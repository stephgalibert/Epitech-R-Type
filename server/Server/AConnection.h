#pragma once

#include <memory>
#include "RequestHandler.h"

class ConnectionManager;
class Party;
class PartyManager;

class AConnection : public std::enable_shared_from_this<AConnection>
{
public:
	const std::shared_ptr<Party> &getCurrentParty(void) const;
	AConnection(PartyManager &pm, RequestHandler &rh, ConnectionManager &cm);
	~AConnection();
	const PartyManager &getPartyManager(void) const;
	const RequestHandler &getRequestHandler(void) const;
	void setID(int id);
private:
	PartyManager &_pm;
	RequestHandler &_rh;
	ConnectionManager &_cm;
	std::shared_ptr<Party> _party;
	int _id;
	bool _ready;
};

