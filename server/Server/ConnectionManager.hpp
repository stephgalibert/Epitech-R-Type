#pragma once

#include <set>
#include <memory>

class AConnection;

class ConnectionManager
{
public:
	ConnectionManager(void);
	~ConnectionManager(void);

	void add(std::shared_ptr<AConnection> connexion);
	void leave(std::shared_ptr<AConnection> connexion);
	void broadcast(std::shared_ptr<AConnection> connexion);
	int getNbConnections(void);
	void closeAll(void);

private:
	std::set<std::shared_ptr<AConnection> > _connections;
};

