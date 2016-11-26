#pragma once

#include "AServer.hpp"

class TCPServer : public AServer
{
public:
	TCPServer(PartyManager &pm);
	virtual ~TCPServer(void);

	virtual void init(void);
	virtual void open(void);
	virtual void close(void);

private:
	IServerSocket *_ss;
};

