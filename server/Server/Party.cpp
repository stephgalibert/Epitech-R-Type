#include "Party.hpp"

Party::Party(void)
	: _launched(false),
	  _mm(_cm, _lm)
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

	connection->setPosition(std::make_pair(x, y));
	connection->setID(id);
	connection->setLife(health);
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
	uint16_t id = connection->getID();

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
		if (connection->getID() == destroyed->id) {
			connection->setLife(connection->getLife() - 1);
			if (connection->getLife() > 0) {
				uint16_t x = connection->getPosition().first;
				uint16_t y = connection->getPosition().second;
				broadcast(std::make_shared<CMDRespawn>(connection->getID(), x, y, connection->getLife()));
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
		_mm.addPlayerScore(owner, collision->id_second);
		broadcast(std::make_shared<CMDScore>(owner->getID(), owner->getScore()));
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
	if (/*_delta > 10.f || */isReady()) {
		//_launched = true;
		broadcast(std::make_shared<CMDGameStatus>(GameStatusType::Playing));
		std::cout << "ready" << std::endl;
		_state = GameStatusType::Playing;
		_delta = 0.;
	}
}

void Party::playing(double delta)
{
	//static bool test = true; // todel

	_delta += delta;
	if (!_cm.isPlayersAlive()) {
		broadcast(std::make_shared<CMDMessage>("No more player alive, game over !"));
		broadcast(std::make_shared<CMDGameStatus>(GameStatusType::GameOver));
		_state = GameStatusType::GameOver;
		_delta = 0.f;
	}
	else if (_mm.noMoreIncoming()) {
		broadcast(std::make_shared<CMDMessage>("No ennemy left, congratulation !"));
		broadcast(std::make_shared<CMDGameStatus>(GameStatusType::GameWin));
		_state = GameStatusType::GameWin;
		_delta = 0.f;
	}
	//else if (_delta > 3.f && test) {
	//	std::cout << "sending span powerup" << std::endl;
	//	broadcast(std::make_shared<CMDSpawnPowerUp>(PowerUPsType::IncreaseNumberOfCanon, _nextID, 200, 200));
	//	//_powerups.insert(_nextID);
	//	++_nextID;
	//	test = false;
	//}

	_mm.update(delta);
}

void Party::gameOver(double delta)
{
	(void)delta;
	_cm.closeAll();
}

void Party::gameWin(double delta)
{
	(void)delta;
	_cm.closeAll();
}
