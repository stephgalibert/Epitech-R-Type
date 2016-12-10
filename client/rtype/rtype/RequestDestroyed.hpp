#pragma once

#include "IRequest.hpp"

class RequestDestroyed : public IRequest
{
public:
	RequestDestroyed(void);
	virtual ~RequestDestroyed(void);

	virtual void execute(IClient &client, std::shared_ptr<ICommand> data,
						 std::shared_ptr<ICommand> &toSend);
};

