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