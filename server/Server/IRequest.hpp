#pragma once

class AConnection;

class IRequest
{
public:
	virtual ~IRequest(void) {}
	virtual void execute(AConnection *server, char *data, char **reply) = 0;
};
