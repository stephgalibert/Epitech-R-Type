#pragma once

#include "ISocket.hpp"
#include "Endpoint.hpp"

struct IUDPSocket : public ISocket
{
	virtual ~IUDPSocket(void) {}

	virtual void init(std::string const& host) = 0;
	virtual void recvFrom(Buffer &buffer, Endpoint &endpoint) = 0;
	virtual void sendTo(char *tosend, size_t len, Endpoint const& endpoint) = 0;
};