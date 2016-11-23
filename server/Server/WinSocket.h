#pragma once
#include "ISocket.hpp"
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

class WinSocket :
	public ISocket {
public:
	enum SocketType {
		TCP = SOCK_STREAM,
		UDP = SOCK_DGRAM
	};
	WinSocket(SocketType type);
	~WinSocket();
	virtual bool connectToServer(std::string const & host, short port);
	virtual bool connectFromAcceptedFd(int fd);
	virtual int recv(std::string& buffer, int blocksize);
	virtual std::string recv();
	virtual int send(std::string const & data);
private:
	SOCKET _socket;
	WSADATA _wsdata;
	SocketType _type;
};

