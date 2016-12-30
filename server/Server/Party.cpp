#include "Party.hpp"

Party::Party(void)
	: _launched(false),
	  _mm(_cm, _lm),
	  _pm(_cm, _lm)
{
	_nextID = 1;
	_state = GameStatusType::Waiting;
	_delta = 0;
	_playersIdAvailable.insert({1, 2, 3, 4});
}

Party::~Party(void)
{
	std::cout << "deleting party " << _name << std::endl;
	_launched = true;
	if (_party.joinable()) {
		_party.join();
	}
}

void Party::init(std::string const& name, std::string const& pwd)
{
	try {
		_name = name;
		_password = pwd;

		_lm.initialize();
		_mm.init();
		_pm.init();
	}
	catch (std::exception const& e) {
	  std::cout << e.what() << std::endl;
		StaticTools::Log << e.what() << std::endl;
	}
}

void Party::run(void)
{
	_party = std::thread(&Party::loop, shared_from_this());
}

void Party::close(void)
{
	_cm.closeAll();
	_launched = true;
	if (_party.joinable()) {
		_party.join();
	}
}

void Party::addConnection(std::shared_ptr<AConnection> connection)
{
	std::lock_guard<std::mutex> lock(_mutex);

	if (_playersIdAvailable.cbegin() == _playersIdAvailable.cend()
		|| _state != GameStatusType::Waiting) {
		std::cout << "rejected" << std::endl;
		return;
	}

	std::pair<short, short> resolution = StaticTools::GetResolution();
	uint16_t id = *_playersIdAvailable.begin();
	_playersIdAvailable.erase(id);
	float percent = (100.f * id / 4.f);
	uint16_t x = _generator(100, 400);
	uint16_t y = _generator((unsigned int)(((percent - 25.f) / 100.f) * (float)resolution.second) + 40,
							(unsigned int)((percent / 100.f) * (float)resolution.second) - 80);
	uint8_t health = 3;

	connection->setPosition(x, y);
	connection->setID(id);
	connection->setLife(health);
	connection->setVelocity(150);
	connection->setAngle(-1);
	// ...

	_cm.newConnection(connection);
	_cm.add(connection);
	connection->sync_write(std::make_shared<CMDGameStatus>(_state));

	std::cout << "new connection" << std::endl;
	broadcast(std::make_shared<CMDMessage>("Player " + connection->getName() + " connected"));
	++_nextID;
}

void Party::removeConnection(std::shared_ptr<AConnection> connection)
{
	std::lock_guard<std::mutex> lock(_mutex);
	uint16_t id = connection->getPlayerData().id;

	_cm.leave(connection);
	broadcast(connection, std::make_shared<CMDDisconnected>(id));
	broadcast(std::make_shared<CMDMessage>("Player " + connection->getName() + " deconnected"));

	_playersIdAvailable.insert(id);
	std::cout << "remove connection" << std::endl;
}

void Party::broadcast(std::shared_ptr<AConnection> connection, std::shared_ptr<ICommand> data)
{
	_cm.broadcast(connection, data);
}

void Party::broadcast(std::shared_ptr<ICommand> data)
{
	_cm.broadcast(data);
}

void Party::move(std::shared_ptr<AConnection> connection, std::shared_ptr<ICommand> cmd)
{
	Move *move = reinterpret_cast<Move *>(cmd->getData());

	if (move->id_tomove < 5) {
		_cm.move(move->id_tomove, move);
	}
	_cm.broadcast(connection, cmd);
}

void Party::fire(std::shared_ptr<ICommand> cmd)
{
	Fire *fire = reinterpret_cast<Fire *>(cmd->getData());
	fire->id = _nextID;
	broadcast(cmd);
	std::lock_guard<std::mutex> lock(_fireMutex);
	_fires.insert(std::make_pair(fire->id, cmd));
	++_nextID;
}

void Party::destroyed(std::shared_ptr<AConnection> connection, std::shared_ptr<ICommand> cmd)
{
	Destroyed const *destroyed = reinterpret_cast<Destroyed const *>(cmd->getData());

	if (!_mm.destroyed(destroyed->id)) {
		if (connection->getPlayerData().id == destroyed->id) {
			connection->setLife(connection->getLife() - 1);
			if (connection->getLife() > 0) {
				uint16_t x = static_cast<uint16_t>(connection->getPlayerData().x);
				uint16_t y = static_cast<uint16_t>(connection->getPlayerData().y);
				broadcast(std::make_shared<CMDRespawn>(connection->getPlayerData().id, x, y, connection->getLife()));
			}
			else {
				broadcast(std::make_shared<CMDMessage>("Player " + connection->getName() + " is dead"));
			}
		}
		else {
			std::lock_guard<std::mutex> lock(_fireMutex);
			if (_fires.find(destroyed->id) != _fires.cend()) {
				_fires.erase(destroyed->id);
			}
		}
	}
}

void Party::collision(std::shared_ptr<AConnection> owner, std::shared_ptr<ICommand> cmd)
{
	Collision const *collision = reinterpret_cast<Collision const *>(cmd->getData());

	if (_fires.find(collision->id_first) != _fires.cend()) {
		_mm.takeDamage(collision->id_second);
		_mm.addPlayerScore(owner, collision->id_second);
		broadcast(std::make_shared<CMDScore>(owner->getPlayerData().id, owner->getScore()));
	}
	else {
		_mm.takeDamage(collision->id_first);
		_mm.takeDamage(collision->id_second);
	}
	broadcast(cmd);
}

void Party::loop(void)
{
	Timer timer;

	while (!isFinished())
	{
		double delta = timer.restart();

		switch (_state)
		{
		case GameStatusType::Waiting:
			waiting(delta);
			break;
		case GameStatusType::Playing:
			playing(delta);
			break;
		case GameStatusType::GameOver:
			gameOver(delta);
			break;
		case GameStatusType::GameWin:
			gameWin(delta);
			break;
		default:
			break;
		}

		StaticTools::Sleep(10);
	}
}

bool Party::isReady(void)
{
	return (_cm.getPlayerNumber() > 1);
}

bool Party::isFinished(void)
{
	return (_launched && !isRunning());
}

bool Party::isRunning(void)
{
	return (_cm.getPlayerNumber() > 0);
}

std::string const& Party::getName(void) const
{
	return (_name);
}

std::string const& Party::getPassword(void) const
{
	return (_password);
}

uint8_t Party::getNbPlayer(void)
{
	return (_cm.getPlayerNumber());
}

void Party::waiting(double delta)
{
	(void)delta;
	//_delta += delta;
	if (_cm.getPlayerNumber() > 0) {
		_launched = true;
	}
	if (isReady()) {
		broadcast(std::make_shared<CMDGameStatus>(GameStatusType::Playing));
		std::cout << "ready" << std::endl;
		_state = GameStatusType::Playing;
		_delta = 0.;
	}
}

void Party::playing(double delta)
{
	_delta += delta;

	_mm.update(delta);
	_pm.update(delta, _nextID);
	_cm.update(delta);

	if (!_cm.isPlayersAlive()) {
		_state = GameStatusType::GameOver;
		_delta = 0.f;
	}
	else if (_mm.noMoreIncoming()) {
		_state = GameStatusType::GameWin;
		_delta = 0.f;
	}
}

void Party::gameOver(double delta)
{
	_delta += delta;

	_cm.update(delta);
	if (_delta > 1.f) {
		broadcast(std::make_shared<CMDMessage>("No more player alive, game over !"));
		broadcast(std::make_shared<CMDGameStatus>(GameStatusType::GameOver));
		_delta = 0.f;
		_cm.closeAll();
	}
}

void Party::gameWin(double delta)
{
	_delta += delta;

	_cm.update(delta);
	if (_delta > 1.f) {
		broadcast(std::make_shared<CMDMessage>("No more ennemy left, congratulation !!!"));
		broadcast(std::make_shared<CMDGameStatus>(GameStatusType::GameWin));
		_delta = 0.f;
		_cm.closeAll();
	}
	//std::cout << _delta << std::endl;
}
