#pragma once

#include "IRequest.hpp"

class RequestFire : public IRequest
{
public:
	RequestFire(void);
	virtual ~RequestFire(void);

	virtual void execute(std::shared_ptr<AConnection> owner,
						 std::shared_ptr<ICommand> received,
						 std::shared_ptr<ICommand> &reply);
};

