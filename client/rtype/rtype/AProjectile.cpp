#include "AProjectile.hpp"

AProjectile::AProjectile(void)
{
}

AProjectile::~AProjectile(void)
{
}

void AProjectile::update(float delta)
{
	(void)delta;
	move(delta);
}

void AProjectile::setOwnerID(uint8_t ownerID)
{
	_ownerID = ownerID;
}