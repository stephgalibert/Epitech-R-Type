#include "AProjectile.hpp"

AProjectile::AProjectile(void)
	: _ownerID(0),
	  _currentLevel(0)
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

uint8_t AProjectile::getOwnerID(void) const
{
	return (_ownerID);
}

void AProjectile::setLevel(uint8_t level)
{
	_currentLevel = level;
}

uint8_t AProjectile::getLevel(void) const
{
	return (_currentLevel);
}