#pragma once

#include "IRequest.hpp"
#include "World.hpp"

class RequestDisconnect : public IRequest
{
public:
	RequestDisconnect(void);
	virtual ~RequestDisconnect(void);

	virtual void execute(IClient &client, std::shared_ptr<ICommand> data,
		std::shared_ptr<ICommand> &toSend);
};

