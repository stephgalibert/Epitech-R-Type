#pragma once

#include "IRequest.hpp"

class RequestScore : public IRequest
{
public:
	RequestScore(void);
	virtual ~RequestScore(void);

	virtual void execute(IClient &client, std::shared_ptr<ICommand> data,
						 std::shared_ptr<ICommand> &toSend);
};

