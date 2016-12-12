#pragma once

#include "AEntity.hpp"
#include "World.hpp"

#include "IRequest.hpp"

class RequestCollision : public IRequest
{
public:
	RequestCollision(void);
	virtual ~RequestCollision(void);

	virtual void execute(IClient &client, std::shared_ptr<ICommand> data,
						 std::shared_ptr<ICommand> &toSend);
};

