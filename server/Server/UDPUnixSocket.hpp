#pragma once

#include "IUDPSocket.hpp"

class UDPUnixSocket : public IUDPSocket
{
public:
	UDPUnixSocket(void);
	virtual ~UDPUnixSocket(void);

	virtual void init(std::string const& host);
	virtual void recvFrom(Buffer &buffer, Endpoint &endpoint);
	virtual void sendTo(char *tosend, size_t len, Endpoint const& endpoint);

private:
	int _socket;
};

