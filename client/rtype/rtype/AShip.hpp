#pragma once

#include "AMoveable.hpp"

#include "World.hpp"
#include "Explosion.hpp"

class AShip : public AMoveable
{
public:
	AShip(void);
	virtual ~AShip(void);

	virtual void init(void) = 0;
	virtual void update(float delta);
	virtual void destroy(void) = 0;

	void shoot(void);

private:
	float _delta;
};

