#include "ADestroyable.hpp"

ADestroyable::ADestroyable(void)
	: _dead(false)
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