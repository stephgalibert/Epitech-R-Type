#pragma once

#include "RequestBuilder.hpp"

class RequestHandler
{
public:
	RequestHandler(void);
	~RequestHandler(void);

	void receive(char *cmd, char **reply);

private:
	RequestBuilder _builder;
};

