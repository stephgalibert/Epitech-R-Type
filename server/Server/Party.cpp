#include "Party.hpp"

Party::Party(void)
	: _launched(false)
{
	_nextID = 1;
	_state = GameStatusType::Waiting;
	_delta = 0;
}

Party::~Party(void)
{
	if (_party.joinable()) {
		_party.join();
	}
	std::cout << "delete party " << _name << std::endl;
}

void Party::init(std::string const& name, std::string const& pwd)
{
	_name = name;
	_password = pwd;
}

void Party::run(void)
{
	_party = std::thread(&Party::loop, shared_from_this());
}

void Party::close(void)
{
	_cm.closeAll();
}

void Party::addConnection(std::shared_ptr<AConnection> connection)
{
	//ObjectType object = ObjectType::Ship;
	uint8_t id = _nextID;
	uint16_t x = 100;
	uint16_t y = 60 * (_cm.getPlayerNumber() + 1);
	uint8_t health = 3;
	/*uint8_t type = (uint8_t)ShipType::Standard;
	  uint8_t effect = 0;*/

	connection->setPosition(std::make_pair(x, y));
	connection->setID(id);
	connection->setLife(health);
	// ...

	_cm.add(connection);
	std::cout << "new connection" << std::endl;

	++_nextID;
}

void Party::removeConnection(std::shared_ptr<AConnection> connection)
{
	uint16_t id = connection->getID();

	_cm.leave(connection);
	_cm.broadcast(connection, std::make_shared<CMDDisconnected>(id));
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
	++_nextID;
	std::cout << "next id: " << (int)_nextID << std::endl;
}

void Party::destroyed(std::shared_ptr<AConnection> connection, std::shared_ptr<ICommand> cmd)
{
	Destroyed *destroyed = reinterpret_cast<Destroyed *>(cmd->getData());

	if (connection->getID() == destroyed->id) {
		connection->setLife(connection->getLife() - 1);
		if (connection->getLife() > 0) {
			uint16_t x = connection->getPosition().first;
			uint16_t y = connection->getPosition().second;
			broadcast(std::make_shared<CMDRespawn>(connection->getID(), x, y, connection->getLife()));
		}
	}
}

void Party::loop(void)
{
	while (!isFinished())
	{
		float delta = _timer.restart();

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

	}
}


bool Party::isReady(void) const
{
	return (_cm.getPlayerNumber() > 1);
}

bool Party::isFinished(void) const
{
	return (_launched && !isRunning());
}

bool Party::isRunning(void) const
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

uint8_t Party::getNbPlayer(void) const
{
	return (_cm.getPlayerNumber());
}

void Party::reset(void)
{
	_nextID = 5;
	_cm.reset();
}

void Party::waiting(float delta)
{
  (void)delta;
	if (isReady()) {
		_launched = true;
		broadcast(std::make_shared<CMDGameStatus>(GameStatusType::Playing));
		_cm.distributeShipID();
		_cm.sendSpawnedShip();
		std::cout << "ready" << std::endl;
		_state = GameStatusType::Playing;
		_delta = 0;
	}
}

void Party::playing(float delta)
{
  (void)delta;
	if (!_cm.isPlayersAlive()) {
		broadcast(std::make_shared<CMDGameStatus>(GameStatusType::GameOver));
		_state = GameStatusType::GameOver;
		_delta = 0;
	}
	// ...
}

void Party::gameOver(float delta)
{
	_delta += delta;
	if (_delta > 10.f) {
		std::cout << "restarting" << std::endl;
		broadcast(std::make_shared<CMDGameStatus>(GameStatusType::Waiting));
		_state = GameStatusType::Waiting;
		_delta = 0;
		reset();
	}
	else {
		std::cout << "game over" << std::endl;
	}
}

void Party::gameWin(float delta)
{
	_delta += delta;
	if (_delta > 10.f) {
		std::cout << "restarting" << std::endl;
		//_cm.broadcast(std::make_shared<CMDGameStatus>(GameStatusType::GameWin));
		broadcast(std::make_shared<CMDGameStatus>(GameStatusType::Waiting));
		_state = GameStatusType::Waiting;
		_delta = 0;
		reset();
	}
	else {
		std::cout << "game win" << std::endl;
	}
}
