#pragma once

#include "AShip.hpp"

class ANPC : public AShip
{
public:
	ANPC();
	virtual ~ANPC();

	virtual void init(void) = 0;
	virtual void update(float delta) = 0;
	virtual void destroy(void) = 0;
};

