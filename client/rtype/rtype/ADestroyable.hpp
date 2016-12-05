#pragma once

#include "AActor.hpp"

class ADestroyable : public AActor
{
public:
	ADestroyable();
	virtual ~ADestroyable();

	virtual void init(void) = 0;
	virtual void update(float delta) = 0;
	virtual void destroy(void) = 0;

	virtual void collision(IClient *client, ACollidable *other) = 0;
};

