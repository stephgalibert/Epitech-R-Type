#pragma once

#include "IRequest.hpp"

class RequestMessage : public IRequest
{
public:
	RequestMessage(void);
	virtual ~RequestMessage(void);

	virtual void execute(IClient &client, std::shared_ptr<ICommand> data,
						 std::shared_ptr<ICommand> &toSend);
};

