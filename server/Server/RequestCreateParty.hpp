#pragma once

#include "IRequest.hpp"

class RequestCreateParty : public IRequest
{
public:
	RequestCreateParty(void);
	virtual ~RequestCreateParty(void);

	virtual void execute(std::shared_ptr<AConnection> owner,
						 std::shared_ptr<ICommand> received,
						 std::shared_ptr<ICommand> &reply);
};