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
	void broadcast(std::shared_ptr<AConnection> connection, std::shared_ptr<ICommand> command);
	void broadcast(std::shared_ptr<ICommand> command);
	void asyncBroadcast(std::shared_ptr<ICommand> command);
	void closeAll(void);

	void newConnection(std::shared_ptr<AConnection> connection);

	uint8_t getPlayerNumber(void);
	bool isPlayersAlive(void);

private:
	std::set<std::shared_ptr<AConnection> > _connections;
	std::mutex _mutex;
};

