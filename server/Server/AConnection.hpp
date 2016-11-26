#pragma once

#include <memory>

#include "RequestHandler.hpp"

class ConnectionManager;
class Party;
class PartyManager;

class AConnection : public std::enable_shared_from_this<AConnection>
{
public:
	AConnection(PartyManager &pm, RequestHandler &rh, ConnectionManager &cm);
	~AConnection(void);

	PartyManager const& getPartyManager(void) const;
	RequestHandler const& getRequestHandler(void) const;

	std::shared_ptr<Party> getCurrentParty(void) const;
	void setID(int id);
private:
	PartyManager &_pm;
	RequestHandler &_rh;
	ConnectionManager &_cm;
	std::shared_ptr<Party> _party;
	int _id;
	bool _ready;
};

