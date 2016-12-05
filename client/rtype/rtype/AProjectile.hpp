#pragma once

#include "AMoveable.hpp"

class AProjectile : public AMoveable
{
public:
	AProjectile(void);
	virtual ~AProjectile(void);

	virtual void init(void) = 0;
	virtual void update(float delta);
	virtual void destroy(void) = 0;

	virtual void collision(IClient *client, ACollidable *other) = 0;

	void setOwnerID(uint8_t ownerID);

private:
	uint8_t _ownerID;
};

