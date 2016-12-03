#pragma once

#include "ANPC.hpp"

class Mate : public ANPC
{
public:
	Mate(void);
	virtual ~Mate(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(void);

private:
	uint8_t _prevDirection;
};

