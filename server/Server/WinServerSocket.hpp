#pragma once

#include <string>

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#include "IServerSocket.hpp"
#include "TCPWinSocket.hpp"

class WinServerSocket : public IServerSocket
{
public:
	WinServerSocket(void);
	virtual ~WinServerSocket(void);

	virtual void init(std::string const &listenHost, short listenPort);
	virtual std::shared_ptr<ITCPSocket> accept();

private:
	SOCKET _socket;
	WSADATA _wsdata;
	std::string _host;
	short _port;
};

