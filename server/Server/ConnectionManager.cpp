#include "ConnectionManager.hpp"
#include "AConnection.hpp"

ConnectionManager::ConnectionManager(void)
{
}

ConnectionManager::~ConnectionManager(void)
{
}

void ConnectionManager::add(std::shared_ptr<AConnection> connection)
{
	_connections.insert(connection);
}

void ConnectionManager::leave(std::shared_ptr<AConnection> connection)
{
	_connections.erase(connection);
}

void ConnectionManager::broadcast(std::shared_ptr<ICommand> command)
{
	for (auto &it : _connections) {
		std::cout << "broadcasting to " << (int)it->getID() << std::endl;
		it->sync_write(command);
	}
}

void ConnectionManager::sendSpawnedShipTo(std::shared_ptr<AConnection> connection)
{
	//for (auto &it : _connections) {
	//	ObjectType object = ObjectType::Ship;
	//	uint8_t id = it->getID();
	//	uint16_t x = it->getPosition().first;
	//	uint16_t y = it->getPosition().second;
	//	uint8_t type = (uint8_t)ShipType::Standard;
	//	uint8_t effect = 0;
	//	bool player = false;

	//	std::cout << "send to " << (int)it->getID() << std::endl;
	//	connection->sync_write(std::make_shared<CMDSpawn>(object, id, x, y, type, effect));
	//}
}

void ConnectionManager::closeAll(void)
{
	_connections.clear();
}

void ConnectionManager::distributeShipID(void)
{
	for (auto &it : _connections) {
		ObjectType object = ObjectType::Ship;
		uint8_t id = it->getID();
		uint16_t x = it->getPosition().first;
		uint16_t y = it->getPosition().second;
		uint8_t type = (uint8_t)ShipType::Standard;
		uint8_t effect = 0;
		bool player = true;

		it->sync_write(std::make_shared<CMDSpawn>(object, id, x, y, type, effect, player));
	}
}

uint8_t ConnectionManager::getPlayerNumber(void) const
{
	return (static_cast<uint8_t>(_connections.size()));
}