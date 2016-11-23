#pragma once
#include "RequestBuilder.h"

class RequestHandler {
public:
	RequestHandler();
	~RequestHandler();
	void receive(char *cmd, char **reply);
private:
	RequestBuilder _builder;
};

