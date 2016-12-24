#pragma once

#include "ADrawable.hpp"
#include "ICommand.hpp"

#define COLLISION_FATAL 1
#define COLLISION_PUP 2
#define COLLISION_NONE 5

class IClient;
class Explosion;
class World;
class AEntity;

class ACollidable : public ADrawable
{
public:
	ACollidable(void);
	virtual ~ACollidable(void);

	virtual void init(void) = 0;
	virtual void update(float delta) = 0;
	virtual void destroy(IClient &client) = 0;

	virtual void collision(IClient *client, AEntity *other) = 0;
	virtual void applyCollision(CollisionType type, AEntity *other) = 0;

	bool isCollidingWith(ACollidable *other);
	sf::FloatRect getBoundingBox(void) const;

	uint8_t getCollisionType(void) const;
	void setCollisionType(uint8_t type);

	bool hasCollisioned(void) const;
	void setCollisioned(bool value);

private:
	uint8_t _type;
	bool _collisioned;
};

