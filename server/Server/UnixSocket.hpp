#pragma once

#include <sys/types.h>

#include "ISocket.hpp"
#include "SocketType.hpp"
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

class UnixSocket : public ISocket
{
public:
	UnixSocket(SocketType type);
	virtual ~UnixSocket(void);

	virtual bool connectToServer(std::string const& host, short port);
	virtual bool connectFromAcceptedFd(int fd);
	virtual int recv(char *buffer, size_t blocksize);
	virtual void recv(Buffer &buffer, size_t transferAtLeast);
	virtual int send(char *data, size_t size);

private:
	int _socket;
	SocketType _type;
};

