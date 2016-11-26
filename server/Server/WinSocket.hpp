#pragma once

#include <winsock2.h>

#include "ISocket.hpp"
#include "SocketType.hpp"

#pragma comment(lib, "ws2_32.lib")

class WinSocket : public ISocket
{
public:

public:
	WinSocket(SocketType type);
	virtual ~WinSocket(void);

	virtual bool connectToServer(std::string const & host, short port);
	virtual bool connectFromAcceptedFd(int fd);
	virtual int recv(std::string& buffer, int blocksize);
	virtual std::string recv(void);
	virtual int send(std::string const & data);

private:
	SOCKET _socket;
	WSADATA _wsdata;
	SocketType _type;
};

