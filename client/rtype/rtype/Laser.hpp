#pragma once

#include "AProjectile.hpp"

class Laser : public AProjectile
{
public:
	Laser();
	virtual ~Laser(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(void);

private:

};

