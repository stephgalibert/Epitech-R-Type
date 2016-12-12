#pragma once

#include "IRequest.hpp"

class RequestRespawn : public IRequest
{
public:
	RequestRespawn(void);
	virtual ~RequestRespawn(void);

	virtual void execute(std::shared_ptr<AConnection> owner,
							std::shared_ptr<ICommand> received,
							std::shared_ptr<ICommand> &reply);
};

