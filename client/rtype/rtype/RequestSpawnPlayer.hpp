#pragma once

#include "IRequest.hpp"

class RequestSpawnPlayer : public IRequest
{
public:
	RequestSpawnPlayer(void);
	virtual ~RequestSpawnPlayer(void);

	virtual void execute(IClient &client, std::shared_ptr<ICommand> data,
						std::shared_ptr<ICommand> &toSend);
};

