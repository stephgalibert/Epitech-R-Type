#pragma once

#include "IRequest.hpp"
#include "APowerUp.hpp"
#include "IncreaseNumberOfCanon.hpp"

class RequestSpawnPowerUp : public IRequest
{
public:
	RequestSpawnPowerUp(void);
	virtual ~RequestSpawnPowerUp(void);

	virtual void execute(IClient &client, std::shared_ptr<ICommand> data,
						 std::shared_ptr<ICommand> &toSend);
};

