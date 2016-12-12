#pragma once

#include "IRequest.hpp"

class RequestGameStatus : public IRequest
{
public:
	RequestGameStatus(void);
	virtual ~RequestGameStatus(void);

	virtual void execute(std::shared_ptr<AConnection> owner,
						 std::shared_ptr<ICommand> received,
						 std::shared_ptr<ICommand> &reply);
};

