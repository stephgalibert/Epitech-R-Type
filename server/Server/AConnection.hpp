#pragma once

#include <iostream>
#include <memory>
#include <queue>
#include <functional>

#include "ISocket.hpp"
#include "RequestHandler.hpp"
#include "ICommand.hpp"
#include "CMDPing.hpp"

#include "StaticTools.hpp"
#include "ConnectionManager.hpp"

class Party;
class PartyManager;

class AConnection : public std::enable_shared_from_this<AConnection>
{
public:
	AConnection(ConnectionManager &cm, RequestHandler &rh, PartyManager &pm);
	~AConnection(void);

	virtual void start(void) = 0;
	virtual void close(void) = 0;

	virtual void write(ICommand *command) = 0;

	ConnectionManager &getConnectionManager(void);
	PartyManager &getPartyManager(void);
	RequestHandler &getRequestHandler(void);

	void setCurrentParty(std::shared_ptr<Party> party);
	void setID(int id);
	void setRunning(bool value);
	void setReady(bool value);

	std::shared_ptr<Party> getCurrentParty(void) const;
	int getID(void) const;
	bool isRunning(void) const;
	bool isReady(void) const;

	virtual void do_read(bool error) = 0;
	virtual void do_write(void) = 0;

private:
    ConnectionManager &_cm;
    RequestHandler &_rh;
	PartyManager &_pm;

	std::shared_ptr<Party> _party;
	bool _running;
	int _id;
	bool _ready;
};

