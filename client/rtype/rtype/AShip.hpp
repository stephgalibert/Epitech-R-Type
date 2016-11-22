#pragma once

#include "AMoveable.hpp"

class AShip : public AMoveable
{
public:
	AShip();
	virtual ~AShip();

	virtual void init(void) = 0;
	virtual void update(float delta) = 0;
	virtual void destroy(void) = 0;
};

