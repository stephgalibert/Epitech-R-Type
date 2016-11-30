#pragma once

#include <iostream>
#include <memory>

#include "ICommand.hpp"

class AConnection;

class IRequest
{
public:
	virtual ~IRequest(void) {}

	virtual void execute(std::shared_ptr<AConnection> owner,
						 std::shared_ptr<ICommand> received,
						 std::shared_ptr<ICommand> &reply) = 0;
};
