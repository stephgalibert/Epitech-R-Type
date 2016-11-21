#include "Background.hpp"

Background::Background(ProjectResource &resource)
	: ADrawable(resource)
{
	_test = 0;
}

Background::~Background(void)
{
}

void Background::init(void)
{
	_resolution = StaticTools::GetResolution();
	sf::RectangleShape *shape = new sf::RectangleShape;

	shape->setPosition(sf::Vector2f(0, 0));
	shape->setSize(sf::Vector2f((float)_resolution.x, (float)_resolution.y));

	setShape(shape);
	setTexture(getResource().getTextureByKey("background"));
}

void Background::update(float delta)
{
	_delta += delta;
	if (_delta > 0.04) {
		int tmp = getShape()->getTextureRect().left + std::ceil(delta * 10.f);
		getShape()->setTextureRect(sf::IntRect(tmp, 400, 1920, 1080));
		_delta = 0;
	}
}

void Background::destroy(void)
{

}