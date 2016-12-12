#pragma once

#include "IRequest.hpp"

class RequestGetParty : public IRequest
{
public:
	RequestGetParty(void);
	virtual ~RequestGetParty(void);

	virtual void execute(IClient &client, std::shared_ptr<ICommand> data,
						 std::shared_ptr<ICommand> &toSend);
};

