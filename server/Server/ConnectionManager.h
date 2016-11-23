#pragma once
#include <vector>
#include <memory>

class AConnection;

class ConnectionManager {
public:
	ConnectionManager();
	~ConnectionManager();
	void add(std::shared_ptr<AConnection> connexion);
	void leave(std::shared_ptr<AConnection> connexion);
	void broadcast(std::shared_ptr<AConnection> connexion);
private:
	std::vector<std::shared_ptr<AConnection>> _connections;
};

