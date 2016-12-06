#pragma once

#include "AShip.hpp"

class ANPC : public AShip
{
public:
	ANPC(void);
	virtual ~ANPC(void);

	virtual void init(void) = 0;
	virtual void update(float delta);
	virtual void destroy(void) = 0;

	virtual void collision(IClient *client, ACollidable *other) = 0;

	virtual void shoot(Fire const& param) = 0;
};

