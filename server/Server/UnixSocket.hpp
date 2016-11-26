#pragma once

#include <sys/types.h>

#include "ISocket.hpp"
#include "SocketType.hpp"

class UnixSocket : public ISocket
{
public:
	UnixSocket(SocketType type);
	virtual ~UnixSocket(void);

	virtual bool connectToServer(std::string const & host, short port);
	virtual bool connectFromAcceptedFd(int fd);
	virtual int recv(std::string& buffer, int blocksize);
	virtual std::string recv(void);
	virtual int send(std::string const & data);

private:
	int _socket;
	SocketType _type;
};

