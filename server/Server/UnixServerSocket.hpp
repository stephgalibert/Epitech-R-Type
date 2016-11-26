#pragma once

#include <sys/types.h>

#include "IServerSocket.hpp"
#include "SocketType.hpp"


class UnixServerSocket : public IServerSocket
{
public:
	UnixServerSocket(SocketType type);
	virtual ~UnixServerSocket(void);

	virtual void init(std::string const & listenHost, short listenPort);
	virtual ISocket* accept(void);

private:
	int _socket;
	SocketType _type;
};

