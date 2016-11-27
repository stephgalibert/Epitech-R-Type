#pragma once

#include <map>
#include <functional>

#include "IRequest.hpp"
#include "CommandType.hpp"

class RequestBuilder
{
public:
	RequestBuilder(void);
	~RequestBuilder(void);

	IRequest *create_SpawnRequest(void);
	IRequest *create_MoveRequest(void);
	IRequest *create_CollisionRequest(void);
	IRequest *create_ErrorRequest(void);
	IRequest *create_PingRequest(void);
	IRequest *create_FireRequest(void);
	IRequest *create_GameStatusRequest(void);

private:
	std::map<CommandType, std::function<IRequest *(void)> > _requests;
};

