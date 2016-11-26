#include "AServer.hpp"

AServer::AServer(PartyManager &pm)
	: _pm(pm)
{
}

AServer::~AServer(void)
{
}

PartyManager const& AServer::getPartyManager(void) const
{
	return _pm;
}

RequestHandler const& AServer::getRequestHandler(void) const
{
	return _rh;
}