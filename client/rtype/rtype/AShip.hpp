#pragma once

#include "AMoveable.hpp"

#include "World.hpp"

class AShip : public AMoveable
{
public:
	AShip(void);
	virtual ~AShip(void);

	virtual void init(void) = 0;
	virtual void update(float delta);
	virtual void destroy(void) = 0;

	virtual void collision(IClient *client, AEntity *other) = 0;
	virtual void move(float delta);

	virtual void shoot(Fire const& param) = 0;
};

