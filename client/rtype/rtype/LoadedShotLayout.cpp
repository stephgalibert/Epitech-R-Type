#include "LoadedShotLayout.hpp"

LoadedShotLayout::LoadedShotLayout(void)
{
	_max = false;
	_inverse = false;
	_delta = 0;
	_deltaShot = 0;
	_state = State::Normal;
}

LoadedShotLayout::~LoadedShotLayout(void)
{
}


void LoadedShotLayout::init(void)
{
	_shape = new sf::ConvexShape(4);

	_shape->setPoint(0, sf::Vector2f(20, 0));
	_shape->setPoint(1, sf::Vector2f(167, 0));
	_shape->setPoint(2, sf::Vector2f(20 + 167, 20));
	_shape->setPoint(3, sf::Vector2f(0, 20));

	_color = sf::Color(0, 0, 255, 150);
	_shape->setFillColor(_color);

	setPosition(144.f, 673.f);
	setShape(_shape);
}

void LoadedShotLayout::update(float delta)
{
	switch (_state)
	{
	case LoadedShotLayout::State::Normal:
		updateNormal(delta);
		break;
	case LoadedShotLayout::State::Max:
		updateMax(delta);
		break;
	default:
		break;
	}
}

void LoadedShotLayout::destroy(IClient &client)
{
	(void)client;
}

void LoadedShotLayout::setLoadedShot(float time)
{
	sf::Vector2f size;

	if (time > 0.f) {
		float coef = (100.f * time) / (MAX_LOAD_SHOT / 1000.f);
		size.x = 167.f * (coef / 100.f);
		size.y = 20.;
	}

	if (size.x < size.y) {
		size.x = 0;
		size.y = 0;
	}
	else {
		if (size.x > 167.f) {
			size.x = 167.f;
			_max = true;
		}
		else {
			_max = false;
		}
		_shape->setPoint(0, sf::Vector2f(size.y, 0));
		_shape->setPoint(1, sf::Vector2f(size.x, 0));
		_shape->setPoint(2, sf::Vector2f(size.x + size.y, size.y));
		_shape->setPoint(3, sf::Vector2f(0, size.y));
	}
}

void LoadedShotLayout::updateNormal(float delta)
{
	(void)delta;
	if (_max) {
		_delta = 0;
		_state = State::Max;
	}
}

void LoadedShotLayout::updateMax(float delta)
{
	if (_max) {
		_delta += delta;
		if (_delta > 0.2f) {
			if (_inverse) {
				_color.g = 128;
			}
			else {
				_color.g = 0;
			}
			_inverse = !_inverse;
			_shape->setFillColor(_color);
			_delta = 0;
		}
	}
	else {
		_delta = 0;
		_color = sf::Color(0, 0, 255, 150);
		_shape->setFillColor(_color);
		_state = State::Normal;
	}
}