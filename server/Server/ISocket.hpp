#pragma once

#include <string>

class ISocket {
public:
	virtual ~ISocket() {}
	virtual bool connectToServer(std::string const & host, short port) = 0;
	virtual bool connectFromAcceptedFd(int fd) = 0;
	virtual int recv(std::string& buffer, int blocksize) = 0;
	virtual std::string recv() = 0;
	virtual int send(std::string const & data) = 0;
};
