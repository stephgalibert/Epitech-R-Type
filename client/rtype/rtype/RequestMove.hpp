#pragma once

#include "IRequest.hpp"
#include "World.hpp"

class RequestMove : public IRequest
{
public:
	RequestMove(void);
	virtual ~RequestMove(void);

	virtual void execute(IClient &client, std::shared_ptr<ICommand> data,
		std::shared_ptr<ICommand> &toSend);
};

