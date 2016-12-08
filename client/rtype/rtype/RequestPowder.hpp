#pragma once

#include "IRequest.hpp"

class RequestPowder : public IRequest
{
public:
	RequestPowder(void);
	virtual ~RequestPowder(void);

	virtual void execute(IClient &client, std::shared_ptr<ICommand> data,
		std::shared_ptr<ICommand> &toSend);
};

