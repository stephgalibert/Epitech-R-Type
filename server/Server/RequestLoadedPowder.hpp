#pragma once

#include "IRequest.hpp"

class RequestLoadedPowder : public IRequest
{
public:
	RequestLoadedPowder(void);
	virtual ~RequestLoadedPowder(void);

	void execute(std::shared_ptr<AConnection> owner,
		std::shared_ptr<ICommand> received,
		std::shared_ptr<ICommand> &reply);
};

