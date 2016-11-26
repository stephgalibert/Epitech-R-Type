#include "AServer.hpp"

AServer::AServer(PartyManager &pm)
	: _pm(pm)
{
}

AServer::~AServer(void)
{
}

RequestHandler const& AServer::getRequestHandler(void) const
{
	return _rh;
}

PartyManager &AServer::getPartyManager(void)
{
	return _pm;
}