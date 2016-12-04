#pragma once

#include "IRequest.hpp"

class RequestDestroyed : public IRequest
{
public:
	RequestDestroyed(void);
	virtual ~RequestDestroyed(void);

	virtual void execute(std::shared_ptr<AConnection> owner,
		std::shared_ptr<ICommand> received,
		std::shared_ptr<ICommand> &reply);
};

