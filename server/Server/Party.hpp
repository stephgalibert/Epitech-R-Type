#pragma once

#include <string>
#include <memory>
#include <thread>
#include <mutex>

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

	void move(std::shared_ptr<ICommand> data);
	void fire(std::shared_ptr<ICommand> data);
	void disconnected(std::shared_ptr<ICommand> data);
	void collision(std::shared_ptr<ICommand> data);
	void loop(void);

	bool isReady(void) const;

	std::string const& getName(void) const;
	std::string const& getPassword(void) const;

private:
	std::string _name;
	std::string _password;
	ConnectionManager _cm;

	std::thread _party;
	bool _running;
	Timer _timer;
	std::mutex _mutex;
};

