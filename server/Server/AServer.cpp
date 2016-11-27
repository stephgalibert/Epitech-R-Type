#include "AServer.hpp"

AServer::AServer(ConnectionManager &cm, PartyManager &pm)
	: _cm(cm), _pm(pm)
{
}

AServer::~AServer(void)
{
}

RequestHandler &AServer::getRequestHandler(void)
{
	return _rh;
}

PartyManager &AServer::getPartyManager(void)
{
	return _pm;
}

ConnectionManager &AServer::getConnectionManager(void)
{
	return (_cm);
}