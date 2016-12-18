#pragma once

#include "IRequest.hpp"

class RequestDisconnect : public IRequest
{
public:
	RequestDisconnect(void);
	virtual ~RequestDisconnect(void);

	virtual void execute(std::shared_ptr<AConnection> owner,
						 std::shared_ptr<ICommand> received,
						 std::shared_ptr<ICommand> &reply);
};

