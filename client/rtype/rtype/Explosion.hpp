#pragma once

#include "AExplosion.hpp"

class Explosion : public AExplosion
{
public:
	Explosion(void);
	virtual ~Explosion(void);

	virtual void init(void);
	virtual void destroy(IClient &client);
};

