#pragma once

#include "IClient.hpp"
#include "ICommand.hpp"

struct IRequest
{
	virtual ~IRequest(void) {}

	virtual void execute(IClient &client, std::shared_ptr<ICommand> data,
						 std::shared_ptr<ICommand> &toSend) = 0;
};