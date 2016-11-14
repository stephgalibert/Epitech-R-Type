#include "AEntity.hpp"

AEntity::AEntity(void)
	: _shape(NULL),
	  _texture(NULL),
	  _waitingForRecycle(false)
{
}

AEntity::~AEntity(void)
{
}

void AEntity::recycle(void)
{
	_waitingForRecycle = true;
}

bool AEntity::isWaitingForRecycle(void) const
{
	return (_waitingForRecycle);
}

void AEntity::setShape(sf::Shape *shape)
{
	_shape = shape;
}

void AEntity::setTexture(sf::Texture *texture)
{
	_texture = texture;
}

void AEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = _texture;

	if (_shape) {
		target.draw(*_shape, states);
	}
}