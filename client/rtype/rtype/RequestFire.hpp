#pragma once

#include "IRequest.hpp"
#include "World.hpp"
#include "AProjectile.hpp"
#include "Laser.hpp"

class RequestFire : public IRequest
{
public:
	RequestFire(void);
	virtual ~RequestFire(void);

	virtual void execute(IClient &client, std::shared_ptr<ICommand> data,
						 std::shared_ptr<ICommand> &toSend);
};

