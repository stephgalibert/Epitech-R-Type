#pragma once
#include "PartyManager.h"
#include "RequestHandler.h"

#ifdef _WIN32
#include "WinServerSocket.h"
#else 
#include "UnixServerSocket.h"
#endif

class AServer {
public:
	const PartyManager &getPartyManager(void) const;
	const RequestHandler &getRequestHandler(void) const;
	AServer(PartyManager &pm);
	~AServer();
private:
	PartyManager &_pm;
	RequestHandler _rh;
	ConnectionManager  _cm;
	IServerSocket* _ss;
};

