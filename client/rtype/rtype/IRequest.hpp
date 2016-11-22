#pragma once

#include "IClient.hpp"
#include "Protocol.hpp"

struct IRequest
{
	virtual ~IRequest(void) {}
	virtual void execute(IClient &client, char *data, char **toSend) = 0;
};