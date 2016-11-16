#pragma once

#include "IClient.hpp"
#include "Protocol.hpp"

struct IRequest
{
	virtual ~IRequest(void) {}
	virtual void execute(IClient &client, std::string const& param, Packet **toSend) = 0;
};