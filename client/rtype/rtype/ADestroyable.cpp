#include "ADestroyable.hpp"

ADestroyable::ADestroyable(void)
	: _dead(false),
	  _explode(false)
{
}

ADestroyable::~ADestroyable(void)
{
}


bool ADestroyable::isDead(void) const
{
	return (_dead);
}

void ADestroyable::setDead(bool value)
{
	_dead = value;
}

void ADestroyable::setExplode(bool value)
{
	_explode = value;
}

bool ADestroyable::isExploding(void) const
{
	return (_explode);
}