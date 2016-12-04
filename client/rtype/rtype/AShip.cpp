#include "AShip.hpp"

AShip::AShip(void)
	: _delta(0)
{
	setCollisionType(COLLISION_FATAL);
}

AShip::~AShip(void)
{
}

void AShip::update(float delta)
{
	_delta += delta;
	
	move(delta);
}

void AShip::shoot(void)
{
	if (_delta > 0.5f) {
		Explosion *explosion = World::TheWorld.spawnEntity<Explosion>();
		explosion->setPosition(getPosition());
		_delta = 0.f;
	}
}