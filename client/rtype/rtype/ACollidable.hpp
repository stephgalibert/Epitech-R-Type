#pragma once

#include "ADrawable.hpp"

#define COLLISION_FATAL 1
#define COLLISION_NONE 5

class IClient;
class Explosion;
class World;

class ACollidable : public ADrawable
{
public:
	ACollidable();
	virtual ~ACollidable();

	virtual void init(void) = 0;
	virtual void update(float delta) = 0;
	virtual void destroy(void) = 0;

	void collision(IClient *client, ACollidable *other);
	bool isCollidingWith(ACollidable *other);
	sf::FloatRect getBoundingBox(void) const;

	uint8_t getCollisionType(void) const;
	void setCollisionType(uint8_t type);

private:
	uint8_t _type;
};

