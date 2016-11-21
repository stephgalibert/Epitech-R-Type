#pragma once
#include <sys/types.h>
#include "IServerSocket.hpp"
#include <sys/socket.h>


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
	int _socket;
	SocketType _type;
};

