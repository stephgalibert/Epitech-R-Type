#include "AConnection.hpp"

AConnection::AConnection(PartyManager &pm, RequestHandler &rh, ConnectionManager &cm)
	: _pm(pm), _rh(rh), _cm(cm)
{
}

AConnection::~AConnection(void)
{
}

PartyManager const& AConnection::getPartyManager(void) const
{
	return _pm;
}

RequestHandler const& AConnection::getRequestHandler(void) const
{
	return _rh;
}

std::shared_ptr<Party> AConnection::getCurrentParty(void) const
{
	return this->_party;
}

void AConnection::setID(int id)
{
	_id = id;
}