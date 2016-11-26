#pragma once

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#include "IServerSocket.hpp"
#include "WinSocket.hpp"

class WinServerSocket : public IServerSocket
{
public:
	enum SocketType
	{
		TCP = SOCK_STREAM,
		UDP = SOCK_DGRAM
	};

public:
	WinServerSocket(SocketType type);
	virtual ~WinServerSocket(void);

	virtual bool init(std::string const & listenHost, short listenPort);
	virtual ISocket* accept();

private:
	SOCKET _socket;
	WSADATA _wsdata;
	SocketType _type;
};

