#include "ACollidable.hpp"
#include "Explosion.hpp"
#include "World.hpp"

ACollidable::ACollidable()
{
}

ACollidable::~ACollidable()
{
}

void ACollidable::collision(IClient *client, ACollidable *other)
{
	if (getCollisionType() != COLLISION_NONE
		&& other->getCollisionType() == COLLISION_FATAL) {

		recycle();
		other->recycle();

		//std::cout << "explosion" << std::endl;

		Explosion *explosion = World::TheWorld.spawnEntity<Explosion>();
		explosion->setPosition(getPosition());

		/*explosion = World::TheWorld.spawnEntity<Explosion>();
		explosion->setPosition(other->getPosition());*/
	}
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
	bounds.top = position.y;
	bounds.left = position.x;
	
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