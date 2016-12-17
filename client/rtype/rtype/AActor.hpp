#pragma once

#include "AEntity.hpp"

class AActor : public AEntity
{
public:
	AActor(void);
	virtual ~AActor(void);

	virtual void init(void) = 0;
	virtual void update(float delta) = 0;
	virtual void destroy(void) = 0;

	virtual void collision(IClient *client, AEntity *other) = 0;
	virtual void applyCollision(CollisionType type, AEntity *other) = 0;
	virtual void move(float delta) = 0;
};

