#pragma once

#include "AMoveable.hpp"

class AProjectile : public AMoveable
{
public:
	AProjectile(void);
	virtual ~AProjectile(void);

	virtual void init(void) = 0;
	virtual void update(float delta) = 0;
	virtual void destroy(void) = 0;
};

