#include "ConnectionManager.hpp"
#include "AConnection.hpp"

ConnectionManager::ConnectionManager(void)
{
}

ConnectionManager::~ConnectionManager(void)
{
}

void ConnectionManager::add(std::shared_ptr<AConnection> connexion)
{
	_connections.insert(connexion);
}

void ConnectionManager::leave(std::shared_ptr<AConnection> connexion)
{
	_connections.erase(connexion);
}

void ConnectionManager::broadcast(std::shared_ptr<AConnection> connexion, char *data)
{
	(void)data;
	(void)connexion;
}

void ConnectionManager::closeAll(void)
{
	_connections.clear();
}

size_t ConnectionManager::getPlayerNumber(void) const
{
	return (_connections.size());
}