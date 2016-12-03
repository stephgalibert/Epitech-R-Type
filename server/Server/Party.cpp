#include "Party.hpp"

Party::Party(void)
{
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
	std::lock_guard<std::mutex> lock(_mutex);

	ObjectType object = ObjectType::Ship;
	uint8_t id = _cm.getPlayerNumber() + 1;
	uint16_t x = 20;
	uint16_t y = 20 * (_cm.getPlayerNumber() + 1);
	uint8_t type = (uint8_t)ShipType::Standard;
	uint8_t effect = 0;

	connection->setPosition(std::make_pair(x, y));
	connection->setID(id);
	// ...

	_cm.add(connection);
	std::cout << "new connection" << std::endl;
}

void Party::removeConnection(std::shared_ptr<AConnection> connection)
{
	std::lock_guard<std::mutex> lock(_mutex);
	uint8_t id = connection->getID();

	_cm.leave(connection);
	_cm.broadcast(connection, std::make_shared<CMDDisconnected>(id));
	std::cout << "remove connection" << std::endl;
}

void Party::move(std::shared_ptr<AConnection> connection, std::shared_ptr<ICommand> data)
{
	_cm.broadcast(connection, data);
}

void Party::fire(std::shared_ptr<AConnection> connection, std::shared_ptr<ICommand> data)
{
	_cm.broadcast(connection, data);
}

void Party::collision(std::shared_ptr<ICommand> data)
{
  (void)data;
}

void Party::loop(void)
{
	while (!isReady());

	std::cout << "ready" << std::endl;

	_cm.distributeShipID();
	_cm.sendSpawnedShip();

	while (true) {
	}
}

bool Party::isReady(void) const
{
	return (_cm.getPlayerNumber() > 1);
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
