#pragma once

#include "StaticTools.hpp"
#include "PartyManager.hpp"
#include "RequestHandler.hpp"
#include "ConnectionManager.hpp"
#include "ThreadPool.hpp"

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

	RequestHandler const& getRequestHandler(void) const;
	PartyManager &getPartyManager(void);

private:
	PartyManager &_pm;
	RequestHandler _rh;
	ConnectionManager  _cm;
};

