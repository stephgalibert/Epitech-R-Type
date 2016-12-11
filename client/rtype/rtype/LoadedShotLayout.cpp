#include "LoadedShotLayout.hpp"

LoadedShotLayout::LoadedShotLayout(void)
{
	_decrease = false;
	_delta = 0;
	_deltaShot = 0;
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

	_shape->setFillColor(sf::Color(0, 0, 255, 150));

	setPosition(144.f, 673.f);
	setShape(_shape);
}

void LoadedShotLayout::update(float delta)
{
	//_delta += delta;
	//if (_decrease) {
	//	if (_deltaShot > 0) {
	//		float diff = _deltaShot - delta;
	//		_deltaShot -= delta;
	//		std::cout << "diff: " << diff << std::endl;
	//		//setLoadedShot(-diff);
	//	}
	//	else {
	//		_deltaShot = 0.f;
	//		_decrease = false;
	//	}
	//}
}

void LoadedShotLayout::destroy(void)
{

}

void LoadedShotLayout::setLoadedShot(float time)
{
	sf::Vector2f size;

	if (time > 0.f) {
		float coef = (100.f * time) / (MAX_LOAD_SHOT / 1000.f);
		size.x = 167.f * (coef / 100.f);
		size.y = 20.;
	}

	//if (time == 0.f && _deltaShot > 0) {
	//	_decrease = true;
	//}
	
	//if (time > 0.f) {
		if (size.x < size.y) {
			size.x = 0;
			size.y = 0;
			//_decrease = true;
		}
		else {
			if (size.x > 167.f) {
				size.x = 167.f;
			}
			//else {
			//	_deltaShot += time;
			//}
			_shape->setPoint(0, sf::Vector2f(size.y, 0));
			_shape->setPoint(1, sf::Vector2f(size.x, 0));
			_shape->setPoint(2, sf::Vector2f(size.x + size.y, size.y));
			_shape->setPoint(3, sf::Vector2f(0, size.y));
		}
	//}
}