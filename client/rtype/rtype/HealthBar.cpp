#include "HealthBar.hpp"

const float HealthBar::MAX_HEALTH = 3.f;

HealthBar::HealthBar(void)
{
	_shape = NULL;
	_resolution = StaticTools::GetResolution();
	_health = 0;
	_delta = 0;
	_deltaLife = 0;
	_inverse = false;
	_state = State::HealthOn;
}

HealthBar::~HealthBar(void)
{
}

void HealthBar::init(void)
{
	_initSize = sf::Vector2f(20, 157);
	_initPos = sf::Vector2f(20 + 6, _resolution.second - 289.f);

	_shape = new sf::ConvexShape(4);
	_shape->setPoint(0, sf::Vector2f(0, 0));
	_shape->setPoint(1, sf::Vector2f(_initSize.x, _initSize.x));
	_shape->setPoint(2, sf::Vector2f(_initSize.x, _initSize.x + _initSize.y));
	_shape->setPoint(3, sf::Vector2f(0, _initSize.y));

	_color = sf::Color(170, 0, 0, 180);
	_shape->setFillColor(_color);

	setPosition(_initPos);
	setShape(_shape);
}

void HealthBar::update(float delta)
{
	switch (_state)
	{
	case HealthBar::State::HealthOn:
		updateHealthOn(delta);
		break;
	case HealthBar::State::HealthOff:
		updateHealthOff(delta);
		break;
	default:
		break;
	}
}

void HealthBar::destroy(IClient &client)
{
	(void)client;
}

void HealthBar::setHealth(uint8_t HealthBar)
{
	if (HealthBar > MAX_HEALTH)
		return;

	_health = HealthBar;
	if (_health < 3) {
		_deltaLife = 3;
	}

	float coef = (100.f * HealthBar) / MAX_HEALTH;
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

void HealthBar::updateHealthOn(float delta)
{
  (void)delta;
	if (_deltaLife > 0.f) {
		_delta = 0;
		_state = State::HealthOff;
	}
}

void HealthBar::updateHealthOff(float delta)
{
	if (_deltaLife > 0.f) {
		_delta += delta;
		if (_delta > 0.2f) {
			if (_inverse) {
				_color.a = 40;
			}
			else {
				_color.a = 180;
			}
			_inverse = !_inverse;
			_shape->setFillColor(_color);
			_delta = 0;
		}
		_deltaLife -= delta;
	}
	else {
		_delta = 0;
		_state = State::HealthOn;
		_color.a = 180;
		_shape->setFillColor(_color);
		_inverse = false;
	}
}
