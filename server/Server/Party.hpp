#pragma once

#include <string>
#include <memory>
#include <thread>

#include "ConnectionManager.hpp"
#include "AConnection.hpp"
#include "Timer.hpp"

class Party : public std::enable_shared_from_this<Party>
{
public:
	Party(void);
	~Party(void);

	void init(std::string const& name, std::string const& pwd);
	void run(void);
	void close(void);

	void addConnection(std::shared_ptr<AConnection> connection);
	void removeConnection(std::shared_ptr<AConnection> connection);

	void move(ICommand *data);
	void fire(ICommand *data);
	void disconnected(ICommand *data);
	void collision(ICommand *data);
	void loop(void);

	std::string const& getName(void) const;
	std::string const& getPassword(void) const;

private:
	std::string _name;
	std::string _password;
	ConnectionManager _cm;

	std::thread _party;
	bool _running;
	Timer _timer;
};

