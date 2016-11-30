#pragma once

#include <string>
#include <memory>
#include <thread>

#include "ConnectionManager.hpp"
#include "AConnection.hpp"

class Party : public std::enable_shared_from_this<Party>
{
public:
	Party(void);
	~Party(void);

	void init(std::string name, std::string pwd);
	void run(void);
	void close(void);

	void addConnection(std::shared_ptr<AConnection> connection);
	void removeConnection(std::shared_ptr<AConnection> connection);

	void move(char *data);
	void fire(char *data);
	void disconnected(char *data);
	void collision(char *data);
	void loop(void);
	bool isReady(void);
	void broadcastToPlayers(std::string const& data);

	std::string const& getName(void) const;
	std::string const& getPassword(void) const;

private:
	std::string _name;
	std::string _password;
	ConnectionManager _cm;

	std::thread _party;
	bool _running;
	//Timer _timer;
};

