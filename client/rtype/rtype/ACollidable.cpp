#include "ACollidable.hpp"

ACollidable::ACollidable()
{
}

ACollidable::~ACollidable()
{
}

bool ACollidable::isCollidingWith(ACollidable *other)
{
	return (other->getBoundingBox().intersects(getBoundingBox()));
}

sf::FloatRect ACollidable::getBoundingBox(void) const
{
	return (getShape()->getGlobalBounds());
}