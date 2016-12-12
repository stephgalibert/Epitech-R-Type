#include "Health.hpp"

const float Health::MAX_HEALTH = 3.f;

Health::Health(void)
{
	_shape = NULL;
	_resolution = StaticTools::GetResolution();
}

Health::~Health(void)
{
}

void Health::init(void)
{
	_initSize = sf::Vector2f(20, 157);
	_initPos = sf::Vector2f(20 + 6, _resolution.second - 289.f);

	_shape = new sf::ConvexShape(4);
	_shape->setPoint(0, sf::Vector2f(0, 0));
	_shape->setPoint(1, sf::Vector2f(_initSize.x, _initSize.x));
	_shape->setPoint(2, sf::Vector2f(_initSize.x, _initSize.x + _initSize.y));
	_shape->setPoint(3, sf::Vector2f(0, _initSize.y));
	
	_shape->setFillColor(sf::Color(170, 0, 0, 180));

	setPosition(_initPos);
	setShape(_shape);
}

void Health::update(float delta)
{

}

void Health::destroy(void)
{

}

void Health::setHealth(uint8_t health)
{
	if (health < 0 || health > MAX_HEALTH)
		return;

	float coef = (100.f * health) / MAX_HEALTH;
	sf::Vector2f size;
	sf::Vector2f pos;

	size.x = _initSize.x;
	size.y = _initSize.y * (coef / 100.f);

	_shape->setPoint(0, sf::Vector2f(0, 0));
	_shape->setPoint(1, sf::Vector2f(size.x, size.x));
	_shape->setPoint(2, sf::Vector2f(size.x, size.x + size.y));
	_shape->setPoint(3, sf::Vector2f(0, size.y));

	coef = 100 - coef;
	pos.x = _initPos.x;
	pos.y = _initPos.y + _initSize.y * (coef / 100.f);
	setPosition(pos);
}