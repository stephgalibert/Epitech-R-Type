#pragma once

#include <winsock2.h>
#include <mutex>
#include <ws2tcpip.h>
#include "ITCPSocket.hpp"
#include "Buffer.hpp"

#pragma comment(lib, "ws2_32.lib")

class TCPWinSocket : public ITCPSocket
{
public:

public:
	TCPWinSocket(void);
	virtual ~TCPWinSocket(void);

	//virtual bool connectToServer(std::string const& host, short port);
	virtual bool connectFromAcceptedFd(int fd);
	virtual int recv(char *buffer, size_t blocksize);
	virtual bool recv(Buffer &buffer, size_t transferAtLeast);
	virtual int send(char *data, size_t size);

private:
	SOCKET _socket;
	WSADATA _wsdata;
};

