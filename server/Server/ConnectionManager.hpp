#pragma once

#include <set>
#include <memory>
#include <mutex>

#include "ICommand.hpp"

class AConnection;

class ConnectionManager
{
public:
	ConnectionManager(void);
	~ConnectionManager(void);

	void add(std::shared_ptr<AConnection> connection);
	void leave(std::shared_ptr<AConnection> connection);
	void broadcast(std::shared_ptr<ICommand> command);
	void sendSpawnedShipTo(std::shared_ptr<AConnection> connection);
	void closeAll(void);

	void distributeShipID(void);
	uint8_t getPlayerNumber(void) const;

private:
	std::set<std::shared_ptr<AConnection> > _connections;
	std::mutex _mutex;
};

