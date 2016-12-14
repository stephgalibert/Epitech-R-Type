#include "AShip.hpp"

AShip::AShip(void)
{
	setCollisionType(COLLISION_FATAL);
	_score = 0;
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

void AShip::setScore(uint16_t score)
{
	_score = score;
}

uint16_t AShip::getScore(void) const
{
	return (_score);
}