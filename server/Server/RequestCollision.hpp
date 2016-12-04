#pragma once

#include <memory>

#include "IRequest.hpp"


class RequestCollision : public IRequest
{
public:
	RequestCollision();
	virtual ~RequestCollision(void);

	virtual void execute(std::shared_ptr<AConnection> owner,
						 std::shared_ptr<ICommand> received,
						 std::shared_ptr<ICommand> &reply);
};

