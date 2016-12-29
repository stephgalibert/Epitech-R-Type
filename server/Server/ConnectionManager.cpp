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

	//connection->setCurrentParty(NULL);
	_connections.erase(connection);
}

void ConnectionManager::broadcast(std::shared_ptr<AConnection> connection, std::shared_ptr<ICommand> command)
{
	std::lock_guard<std::mutex> lock(_mutex);

	for (auto &it : _connections) {
		if (it->getPlayerData().id != connection->getPlayerData().id) {
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

void ConnectionManager::asyncBroadcast(std::shared_ptr<ICommand> command)
{
	std::lock_guard<std::mutex> lock(_mutex);

	for (auto &it : _connections) {
		it->write(command);
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

	uint16_t id = connection->getPlayerData().id;
	uint16_t x = static_cast<uint16_t>(connection->getPlayerData().x);
	uint16_t y = static_cast<uint16_t>(connection->getPlayerData().y);
	uint8_t health = connection->getLife();
	//float velocity = connection->getVelocity();
	std::string const& name = connection->getName();

	connection->sync_write(std::make_shared<CMDSpawnPlayer>(id, x, y, health, true, name));

	for (auto &it : _connections) {
		it->sync_write(std::make_shared<CMDSpawnPlayer>(id, x, y, health, false, name));
	}

	for (auto &it : _connections) {
		id = it->getPlayerData().id;
		x = static_cast<uint16_t>(it->getPlayerData().x);
		y = static_cast<uint16_t>(it->getPlayerData().y);
		health = it->getLife();
		std::string const& name = it->getName();
		connection->sync_write(std::make_shared<CMDSpawnPlayer>(id, x, y, health, /*velocity, */false, name));
	}
}

std::vector<PlayerData> &ConnectionManager::getPlayersData(void)
{
	_playersData.clear();
	for (auto &it : _connections) {
		if (it->getLife() > 0) {
			_playersData.push_back(it->getPlayerData());
		}
	}
	return (_playersData);
}

void ConnectionManager::move(uint16_t id, Move *move)
{
	for (auto it : _connections) {
		if (it->getPlayerData().id == id) {
			it->setDirection(move->direction);
			uint16_t x = static_cast<uint16_t>(it->getPlayerData().x);
			uint16_t y = static_cast<uint16_t>(it->getPlayerData().y);
			move->position = StaticTools::SerializePosition(x, y);
		}
	}
}

void ConnectionManager::update(double delta)
{
	for (auto &it : _connections) {
		it->update(delta);
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