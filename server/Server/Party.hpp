#pragma once

#include <string>
#include <memory>
#include <thread>
#include <mutex>
#include <set>

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

	void broadcast(std::shared_ptr<AConnection> connection, std::shared_ptr<ICommand> data);
	void broadcast(std::shared_ptr<ICommand> data);
	void fire(std::shared_ptr<ICommand> cmd);
	void loop(void);

	bool isReady(void) const;
	bool isFinished(void) const;
	bool isRunning(void) const;

	std::string const& getName(void) const;
	std::string const& getPassword(void) const;

private:
	std::string _name;
	std::string _password;
	ConnectionManager _cm;

	Timer _timer;
	std::thread _party;
	std::mutex _mutex;
	bool _launched;
	//std::set<uint16_t> _ids;
	uint8_t _nextID;
};

