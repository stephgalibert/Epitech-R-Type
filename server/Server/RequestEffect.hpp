#pragma once

#include "IRequest.hpp"

class RequestEffect : public IRequest
{
public:
	RequestEffect(void);
	virtual ~RequestEffect(void);

	virtual void execute(std::shared_ptr<AConnection> owner,
						 std::shared_ptr<ICommand> received,
						 std::shared_ptr<ICommand> &reply);
};

