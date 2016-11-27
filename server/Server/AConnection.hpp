#pragma once

#include <memory>
#include <queue>

#include "ISocket.hpp"
#include "RequestHandler.hpp"

class ConnectionManager;
class Party;
class PartyManager;

class AConnection : public std::enable_shared_from_this<AConnection>
{
public:
	AConnection(ConnectionManager &cm, RequestHandler &rh, PartyManager &pm);
	~AConnection(void);

	void start(void);
	void close(void);

	PartyManager const& getPartyManager(void) const;
	RequestHandler const& getRequestHandler(void) const;

	std::shared_ptr<Party> getCurrentParty(void) const;
	void setID(int id);

private:
	void read(void);
	void do_read(void);

	void write(void);
	void do_write(void);

	PartyManager &_pm;
	RequestHandler &_rh;
	ConnectionManager &_cm;

	std::shared_ptr<ISocket> _socket;
	//std::queue<ICommand> _toWrites;
	bool _running;

	//std::shared_ptr<Party> _party;
	int _id;
	bool _ready;
};

