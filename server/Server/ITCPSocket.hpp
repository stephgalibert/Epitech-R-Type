#pragma once

#include "ISocket.hpp"

struct ITCPSocket : public ISocket
{
	virtual ~ITCPSocket(void) {}

	virtual bool connectToServer(std::string const & host, short port) = 0;
	virtual bool connectFromAcceptedFd(int fd) = 0;
	virtual int recv(char *buffer, size_t blocksize) = 0;
	virtual bool recv(Buffer &buffer, size_t transferAtLeast) = 0;
	virtual int send(char *data, size_t size) = 0;
};