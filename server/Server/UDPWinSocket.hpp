#pragma once

#include <winsock2.h>

#include "IUDPSocket.hpp"
#include "Endpoint.hpp"

class UDPWinSocket : public IUDPSocket
{
public:
	UDPWinSocket();
	virtual ~UDPWinSocket(void);

	virtual void init(std::string const& host);
	virtual void recvFrom(Buffer &buffer, Endpoint &endpoint);
	virtual void sendTo(char *tosend, size_t len, Endpoint const& endpoint);

private:
	SOCKET _socket;
	WSADATA _wsdata;
};

