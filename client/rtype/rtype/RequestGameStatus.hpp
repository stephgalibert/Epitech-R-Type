#pragma once

#include "IRequest.hpp"

class RequestGameStatus : public IRequest
{
public:
	RequestGameStatus(void);
	virtual ~RequestGameStatus(void);

	virtual void execute(IClient &client, std::shared_ptr<ICommand> data,
						 std::shared_ptr<ICommand> &toSend);
};

