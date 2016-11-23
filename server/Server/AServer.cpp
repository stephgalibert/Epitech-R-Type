#include "AServer.h"



const PartyManager & AServer::getPartyManager(void) const {
	return _pm;
}

const RequestHandler & AServer::getRequestHandler(void) const {
	return _rh;
}

AServer::AServer(PartyManager &pm) : _pm(pm) {}


AServer::~AServer() {}
