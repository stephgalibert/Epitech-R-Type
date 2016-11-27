#pragma once

#include <winsock2.h>

#include "ISocket.hpp"
#include "SocketType.hpp"
#include "Buffer.hpp"

#pragma comment(lib, "ws2_32.lib")

class WinSocket : public ISocket
{
public:

public:
	WinSocket(SocketType type);
	virtual ~WinSocket(void);

	virtual bool connectToServer(std::string const& host, short port);
	virtual bool connectFromAcceptedFd(int fd);
	virtual int recv(char *buffer, size_t blocksize);
	//virtual std::string recv(void);
	virtual void recv(Buffer &buffer, size_t transferAtLeast);
	virtual int send(char *data, size_t size);

private:
	SOCKET _socket;
	WSADATA _wsdata;
	SocketType _type;
};

