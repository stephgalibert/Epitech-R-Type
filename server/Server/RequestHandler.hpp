#pragma once

#include <memory>

#include "RequestBuilder.hpp"
#include "ICommand.hpp"
#include "CommandFactory.hpp"

class AConnection;

class RequestHandler
{
public:
	RequestHandler(void);
	~RequestHandler(void);

	void receive(std::shared_ptr<AConnection> owner,
				 std::shared_ptr<ICommand> received,
				 std::shared_ptr<ICommand> &reply);
};

