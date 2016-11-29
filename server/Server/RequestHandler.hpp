#pragma once

#include <memory>

#include "RequestBuilder.hpp"
//#include "AConnection.hpp"

#include "ICommand.hpp"
#include "CommandFactory.hpp"

class AConnection;

class RequestHandler
{
public:
	RequestHandler(void);
	~RequestHandler(void);

	void receive(std::shared_ptr<AConnection> owner, char *received, ICommand **reply);

private:
	RequestBuilder _reqbuilder;
	CommandFactory _cmdBuilder;
};

