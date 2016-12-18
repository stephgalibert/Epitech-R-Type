#pragma once

#include "IRequest.hpp"
#include "World.hpp"

class RequestDisconnected : public IRequest
{
public:
	RequestDisconnected(void);
	virtual ~RequestDisconnected(void);

	virtual void execute(IClient &client, std::shared_ptr<ICommand> data,
		std::shared_ptr<ICommand> &toSend);
};

