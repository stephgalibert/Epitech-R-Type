#pragma once

#include "IRequest.hpp"

class RequestScore : public IRequest
{
public:
	RequestScore(void);
	virtual ~RequestScore(void);

	virtual void execute(std::shared_ptr<AConnection> owner,
						 std::shared_ptr<ICommand> received,
						 std::shared_ptr<ICommand> &reply);
};