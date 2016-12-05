#include "ACollidable.hpp"
#include "Explosion.hpp"
#include "World.hpp"

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
	if (!getShape()) {
		return sf::FloatRect(0, 0, 0, 0);
	}
	sf::FloatRect bounds = getShape()->getGlobalBounds();
	sf::Vector2f position = getPosition();
	bounds.top = position.y - (bounds.height / 2);
	bounds.left = position.x - (bounds.width / 2);
	
	return (bounds);
}

uint8_t ACollidable::getCollisionType(void) const
{
	return (_type);
}

void ACollidable::setCollisionType(uint8_t type)
{
	_type = type;
}
