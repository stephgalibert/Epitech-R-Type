#include "Party.hpp"

Party::Party(void)
	: _launched(false)
{
	_nextID = 1;
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
	std::lock_guard<std::mutex> lock(_mutex);

	_cm.closeAll();
}

void Party::addConnection(std::shared_ptr<AConnection> connection)
{
	std::lock_guard<std::mutex> lock(_mutex);

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
	std::lock_guard<std::mutex> lock(_mutex);
	uint16_t id = connection->getID();

	_cm.leave(connection);
	_cm.broadcast(connection, std::make_shared<CMDDisconnected>(id));
	std::cout << "remove connection" << std::endl;
}

void Party::broadcast(std::shared_ptr<AConnection> connection, std::shared_ptr<ICommand> data)
{
	std::lock_guard<std::mutex> lock(_mutex);

	_cm.broadcast(connection, data);
}

void Party::broadcast(std::shared_ptr<ICommand> data)
{
	std::lock_guard<std::mutex> lock(_mutex);

	_cm.broadcast(data);
}

void Party::fire(std::shared_ptr<ICommand> cmd)
{
	Fire *fire = reinterpret_cast<Fire *>(cmd->getData());
	fire->id = _nextID;
	_cm.broadcast(cmd);
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
			_cm.broadcast(std::make_shared<CMDRespawn>(connection->getID(), x, y, connection->getLife()));
		}
	}
}

void Party::respawn(std::shared_ptr<ICommand> cmd)
{

}

void Party::loop(void)
{
	while (!isReady());
	_launched = true;

	std::cout << "ready" << std::endl;

	_cm.distributeShipID();
	_cm.sendSpawnedShip();

	while (isRunning());
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