#pragma once
#include "IServerSocket.hpp"
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

class WinServerSocket :
	public IServerSocket {
public:
	enum SocketType {
		TCP = SOCK_STREAM,
		UDP = SOCK_DGRAM
	};
	WinServerSocket(SocketType type);
	virtual ~WinServerSocket();
	virtual bool init(std::string const & listenHost, short listenPort);
	virtual ISocket* accept();
private:
	SOCKET _socket;
	WSADATA _wsdata;
	SocketType _type;
};

