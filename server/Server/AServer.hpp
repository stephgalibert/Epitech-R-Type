#pragma once

#include "PartyManager.hpp"
#include "RequestHandler.hpp"
#include "ConnectionManager.hpp"

#ifdef _WIN32
# include "WinServerSocket.hpp"
#else 
# include "UnixServerSocket.hpp"
#endif

class AServer
{
public:
	AServer(PartyManager &pm);
	~AServer(void);

	PartyManager const& getPartyManager(void) const;
	RequestHandler const& getRequestHandler(void) const;
private:
	PartyManager &_pm;
	RequestHandler _rh;
	ConnectionManager  _cm;
	IServerSocket* _ss;
};

