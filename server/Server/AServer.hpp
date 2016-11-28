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
	AServer(ConnectionManager &cm, PartyManager &pm);
	virtual ~AServer(void);

	virtual void init(void) = 0;
	virtual void open(void) = 0;
	virtual void close(void) = 0;

	RequestHandler &getRequestHandler(void);
	PartyManager &getPartyManager(void);
	ConnectionManager &getConnectionManager(void);

private:
        ConnectionManager &_cm;
	PartyManager &_pm;
	RequestHandler _rh;
};

