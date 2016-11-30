#pragma once

#include "IRequest.hpp"

class RequestSpawn : public IRequest
{
public:
	RequestSpawn();
	virtual ~RequestSpawn(void);

	virtual void execute(IClient &client, std::shared_ptr<ICommand> data,
						 std::shared_ptr<ICommand> &toSend);
};

