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

	virtual void collision(IClient *client, AEntity *other) = 0;
	virtual void applyCollision(CollisionType type, AEntity *other) = 0;
	virtual void move(float delta) = 0;

	bool isDead(void) const;
	void setDead(bool value);

	void setExplode(bool value);
	bool isExploding(void) const;

private:
	bool _dead;
	bool _explode;
};

