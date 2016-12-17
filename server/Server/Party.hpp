#pragma once

#include <string>
#include <memory>
#include <thread>
#include <mutex>
#include <set>

#include "ConnectionManager.hpp"
#include "AConnection.hpp"
#include "Timer.hpp"
#include "Generator.hpp"
#include "MonsterManager.hpp"

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
	void destroyed(std::shared_ptr<AConnection> connection, std::shared_ptr<ICommand> cmd);
	void loop(void);

	bool isReady(void);
	bool isFinished(void);
	bool isRunning(void);

	std::string const& getName(void) const;
	std::string const& getPassword(void) const;

	uint8_t getNbPlayer(void);

private:
	void reset(void);

	void waiting(double delta);
	void playing(double delta);
	void gameOver(double delta);
	void gameWin(double delta);


private:
	std::string _name;
	std::string _password;
	ConnectionManager _cm;

	std::thread _party;
	bool _launched;
	uint8_t _nextID;
	GameStatusType _state;
	double _delta;
	Generator _generator;
	std::set<uint16_t> _playersIdAvailable;
	std::mutex _mutex;

	MonsterManager _mm;
	std::set<uint16_t> _powerups;
};

