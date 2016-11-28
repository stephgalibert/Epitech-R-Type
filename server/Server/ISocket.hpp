#pragma once

#include <string>
#include <memory>

#include "Buffer.hpp"

class ISocket : public std::enable_shared_from_this<ISocket>
{
public:
	virtual ~ISocket(void) {}

	virtual bool connectToServer(std::string const & host, short port) = 0;
	virtual bool connectFromAcceptedFd(int fd) = 0;
	virtual int recv(char *buffer, size_t blocksize) = 0;
	//virtual std::string recv(void) = 0;
	virtual void recv(Buffer &buffer, size_t transferAtLeast) = 0;
	virtual int send(char *data, size_t size) = 0;
};
