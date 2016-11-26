#pragma once

#include "ISocket.hpp"

class IServerSocket
{
public:
	virtual ~IServerSocket(void) {}
	virtual bool init(std::string const & listenHost, short listenPort) = 0;
	virtual ISocket* accept(void) = 0;
};
