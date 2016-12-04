#pragma once

#include "ADestroyable.hpp"

class AMoveable : public ADestroyable
{
public:
	AMoveable();
	virtual ~AMoveable();

	virtual void init(void) = 0;
	virtual void update(float delta) = 0;
	virtual void destroy(void) = 0;
};

