#pragma once

#include <string>
#include <memory>

class ISocket : std::enable_shared_from_this<ISocket>
{
public:
	virtual ~ISocket(void) {}
	virtual bool connectToServer(std::string const & host, short port) = 0;
	virtual bool connectFromAcceptedFd(int fd) = 0;
	virtual int recv(std::string& buffer, int blocksize) = 0;
	virtual std::string recv(void) = 0;
	virtual int send(std::string const & data) = 0;
};
