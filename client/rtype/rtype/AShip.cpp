#include "AShip.hpp"

AShip::AShip(void)
{
	setCollisionType(COLLISION_FATAL);
}

AShip::~AShip(void)
{
}

void AShip::update(float delta)
{
	move(delta);
}

void AShip::move(float delta)
{
	AMoveable::move(delta);
}