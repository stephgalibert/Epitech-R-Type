#pragma once
#include "ISocket.hpp"
#include <sys/types.h>
#include <sys/socket.h>

class UnixSocket :
	public ISocket {
public:
	enum SocketType {
		TCP = SOCK_STREAM,
		UDP = SOCK_DGRAM
	};
	UnixSocket(SocketType type);
	~UnixSocket();
	virtual bool connectToServer(std::string const & host, short port);
	virtual bool connectFromAcceptedFd(int fd);
	virtual int recv(std::string& buffer, int blocksize);
	virtual std::string recv();
	virtual int send(std::string const & data);
private:
	int _socket;
	SocketType _type;
};

