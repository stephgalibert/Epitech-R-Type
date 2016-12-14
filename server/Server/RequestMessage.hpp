#pragma once

#include "IRequest.hpp"

class RequestMessage : public IRequest
{
public:
	RequestMessage(void);
	virtual ~RequestMessage(void);

	virtual void execute(std::shared_ptr<AConnection> owner,
						 std::shared_ptr<ICommand> received,
						 std::shared_ptr<ICommand> &reply);
};

