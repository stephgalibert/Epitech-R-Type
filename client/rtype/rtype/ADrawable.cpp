#include "ADrawable.hpp"
#include "World.hpp"

ADrawable::ADrawable(ProjectResource &resource)
	: _resource(resource),
	  _shape(NULL),
	  _texture(NULL)
{
}

ADrawable::~ADrawable(void)
{
	if (_shape) {
		delete (_shape);
	}
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

ProjectResource &ADrawable::getResource(void)
{
	return (_resource);
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