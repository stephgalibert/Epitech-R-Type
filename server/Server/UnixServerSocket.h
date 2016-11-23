#pragma once
#include <sys/types.h>
#include "IServerSocket.hpp"
#include <sys/socket.h>


class UnixServerSocket :
	public IServerSocket {
public:
	enum SocketType {
		TCP = SOCK_STREAM,
		UDP = SOCK_DGRAM
	};
	UnixServerSocket(SocketType type);
	virtual ~UnixServerSocket();
	virtual bool init(std::string const & listenHost, short listenPort);
	virtual ISocket* accept();
private:
	int _socket;
	SocketType _type;
};

