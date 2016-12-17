#include "APowerUp.hpp"

APowerUp::APowerUp(void)
{
	setCollisionType(COLLISION_PUP);
}

APowerUp::~APowerUp(void)
{
}

void APowerUp::collision(IClient *client, AEntity *other)
{
	(void)other;
	(void)client;
}

void APowerUp::applyCollision(CollisionType type, AEntity *other)
{
	switch (type)
	{
	case CollisionType::None:
		break;
	case CollisionType::Destruction:
		break;
	case CollisionType::PowerUP:
		break;
	default:
		break;
	}
}