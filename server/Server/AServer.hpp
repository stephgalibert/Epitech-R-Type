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

	virtual void init(void) = 0;
	virtual void open(void) = 0;
	virtual void close(void) = 0;

	PartyManager const& getPartyManager(void) const;
	RequestHandler const& getRequestHandler(void) const;
private:
	PartyManager &_pm;
	//IServerSocket *_ss;
	RequestHandler _rh;
	ConnectionManager  _cm;
};

