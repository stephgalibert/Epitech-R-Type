#include "Party.hpp"

Party::Party(void)
	: _launched(false)
{
	_nextID = 1;
	_state = GameStatusType::Waiting;
	_delta = 0;
	_playersIdAvailable.insert({1, 2, 3, 4});
}

Party::~Party(void)
{
	_launched = true;
	if (_party.joinable()) {
		_party.join();
	}
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
	_launched = true;
	if (_party.joinable()) {
		_party.join();
	}
}

void Party::addConnection(std::shared_ptr<AConnection> connection)
{
	std::lock_guard<std::mutex> lock(_mutex);

	if (_playersIdAvailable.cbegin() == _playersIdAvailable.cend()
		|| _launched == true) {
		std::cout << "rejected" << std::endl;
		return;
	}
	//ObjectType object = ObjectType::Ship;
	//uint8_t id = _nextID;
	std::pair<short, short> resolution = StaticTools::GetResolution();
	uint16_t id = *_playersIdAvailable.begin();
	_playersIdAvailable.erase(id);
	float percent = (100.f * id / 4.f);
	uint16_t x = _generator(100, 400);
	uint16_t y = _generator((unsigned int)(((percent - 25.f) / 100.f) * (float)resolution.second) + 40,
							(unsigned int)((percent / 100.f) * (float)resolution.second) - 80);
	uint8_t health = 3;
	/*uint8_t type = (uint8_t)ShipType::Standard;
	  uint8_t effect = 0;*/

	connection->setPosition(std::make_pair(x, y));
	connection->setID(id);
	connection->setLife(health);
	// ...

	_cm.newConnection(connection);
	_cm.add(connection);
	connection->sync_write(std::make_shared<CMDGameStatus>(_state));

	std::cout << "new connection" << std::endl;

	++_nextID;
}

void Party::removeConnection(std::shared_ptr<AConnection> connection)
{
	std::lock_guard<std::mutex> lock(_mutex);
	uint16_t id = connection->getID();

	_cm.leave(connection);
	_cm.broadcast(connection, std::make_shared<CMDDisconnected>(id));
	_cm.broadcast(std::make_shared<CMDMessage>("Player " + std::to_string(id) + " deconnected"));
	
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

		StaticTools::sleep(10);
	}
}

bool Party::isReady(void)
{
	return (_cm.getPlayerNumber() > 3);
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

void Party::reset(void)
{
	_nextID = 5;
	_cm.reset();
}

void Party::waiting(double delta)
{
	_delta += delta;
	if (_delta > 10. || isReady()) {
		_launched = true;
		broadcast(std::make_shared<CMDGameStatus>(GameStatusType::Playing));
		std::cout << "ready" << std::endl;
		_state = GameStatusType::Playing;
		_delta = 0.;
	}
	//std::cout << _delta << std::endl;
}

void Party::playing(double delta)
{
  (void)delta;
	if (!_cm.isPlayersAlive()) {
		broadcast(std::make_shared<CMDGameStatus>(GameStatusType::GameOver));
		_state = GameStatusType::GameOver;
		_delta = 0.f;
	}
	// ...
}

//#include <Windows.h>

void Party::gameOver(double delta)
{
	_delta += delta;
	if (_delta > 10.f) {
		_launched = false;
		std::cout << "restarting" << std::endl;
		broadcast(std::make_shared<CMDGameStatus>(GameStatusType::Waiting));
		_state = GameStatusType::Waiting;
		_delta = 0;
		reset();
		_cm.distributeShipID();
		_cm.sendSpawnedShip();
	}
}

void Party::gameWin(double delta)
{
	_delta += delta;
	if (_delta > 10.0000) {
		_launched = false;
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
