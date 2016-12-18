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
	std::lock_guard<std::mutex> lock(_mutex);

	_connections.insert(connection);
}

void ConnectionManager::leave(std::shared_ptr<AConnection> connection)
{
	std::lock_guard<std::mutex> lock(_mutex);

	_connections.erase(connection);
}

void ConnectionManager::broadcast(std::shared_ptr<AConnection> connection, std::shared_ptr<ICommand> command)
{
	std::lock_guard<std::mutex> lock(_mutex);

	for (auto &it : _connections) {
		if (it->getID() != connection->getID()) {
			it->sync_write(command);
		}
	}
}

void ConnectionManager::broadcast(std::shared_ptr<ICommand> command)
{
	std::lock_guard<std::mutex> lock(_mutex);

	for (auto &it : _connections) {
		it->sync_write(command);
	}
}

void ConnectionManager::closeAll(void)
{
	std::lock_guard<std::mutex> lock(_mutex);

	for (auto &it : _connections) {
		it->setCurrentParty(NULL);
	}
	_connections.clear();
}

void ConnectionManager::newConnection(std::shared_ptr<AConnection> connection)
{
	std::lock_guard<std::mutex> lock(_mutex);

	uint16_t id = connection->getID();
	uint16_t x = connection->getPosition().first;
	uint16_t y = connection->getPosition().second;
	uint8_t health = connection->getLife();
	std::string const& name = connection->getName();

	connection->sync_write(std::make_shared<CMDSpawnPlayer>(id, x, y, health, true, name));

	for (auto &it : _connections) {
		it->sync_write(std::make_shared<CMDSpawnPlayer>(id, x, y, health, false, name));
	}

	for (auto &it : _connections) {
		id = it->getID();
		x = it->getPosition().first;
		y = it->getPosition().second;
		health = it->getLife();
		std::string const& name = it->getName();
		connection->sync_write(std::make_shared<CMDSpawnPlayer>(id, x, y, health, false, name));
	}
}

uint8_t ConnectionManager::getPlayerNumber(void)
{
	std::lock_guard<std::mutex> lock(_mutex);
	return (static_cast<uint8_t>(_connections.size()));
}

bool ConnectionManager::isPlayersAlive(void)
{
	std::lock_guard<std::mutex> lock(_mutex);

	uint8_t nb = 0;

	for (auto &it : _connections) {
		if (it->getLife() > 0) {
			++nb;
		}
	}
	return (nb > 0);
}