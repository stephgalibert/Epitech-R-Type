#pragma once

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#include "IServerSocket.hpp"
#include "SocketType.hpp"
#include "WinSocket.hpp"

class WinServerSocket : public IServerSocket
{
public:
	WinServerSocket(SocketType type);
	virtual ~WinServerSocket(void);

	virtual void init(std::string const & listenHost, short listenPort);
	virtual ISocket* accept();

private:
	SOCKET _socket;
	WSADATA _wsdata;
	SocketType _type;
};

