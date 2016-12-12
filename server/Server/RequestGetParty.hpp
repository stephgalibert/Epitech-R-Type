#pragma once

#include "IRequest.hpp"

class RequestGetParty :public IRequest
{
public:
	RequestGetParty(void);
	virtual ~RequestGetParty(void);

	virtual void execute(std::shared_ptr<AConnection> owner,
						 std::shared_ptr<ICommand> received,
						 std::shared_ptr<ICommand> &reply);
};

