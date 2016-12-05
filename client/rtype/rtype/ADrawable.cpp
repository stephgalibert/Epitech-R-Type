#include "ADrawable.hpp"

ADrawable::ADrawable()
  : _shape(NULL),
	_texture(NULL),
	_waitingForRecycle(false),
	_init(false)
{
}

ADrawable::~ADrawable(void)
{
	if (_shape) {
		delete (_shape);
	}
}

void ADrawable::recycle(void)
{
	_waitingForRecycle = true;
}

bool ADrawable::isWaitingForRecycle(void) const
{
	return (_waitingForRecycle);
}

void ADrawable::setInit(bool value)
{
	_init = value;
}

bool ADrawable::isInitialized(void) const
{
	return (_init);
}

void ADrawable::setShape(sf::Shape *shape)
{
	_shape = shape;
}

void ADrawable::setTexture(sf::Texture *texture)
{
	_texture = texture;
	if (_shape) {
		_shape->setTexture(texture);
	}
}

sf::Shape *ADrawable::getShape(void) const
{
	return (_shape);
}

sf::Texture *ADrawable::getTexture(void) const
{
	return (_texture);
}

void ADrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	if (_texture) {
		states.texture = _texture;
	}

	if (_shape) {
		target.draw(*_shape, states);
	}
}
