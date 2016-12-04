#include "AShip.hpp"

AShip::AShip(void)
	: _delta(0),
	  _deltaLastShoot(0),
	  _targetFrame(0),
      _currentFrame(0)
{
	setCollisionType(COLLISION_FATAL);
}

AShip::~AShip(void)
{
}

void AShip::update(float delta)
{
	_delta += delta;
	_deltaLastShoot += delta;
	
	updateFrame();
	move(delta);
}

void AShip::setTargetFrame(uint8_t targetFrame)
{
	_targetFrame = targetFrame;
}

void AShip::setCurrentFrame(uint8_t currentFrame)
{
	_currentFrame = currentFrame;
}

void AShip::shoot(void)
{
	if (_deltaLastShoot > 0.5f) {
		Explosion *explosion = World::TheWorld.spawnEntity<Explosion>();
		explosion->setPosition(getPosition());
		_deltaLastShoot = 0.f;
	}
}

void AShip::updateFrame(void)
{
	if (_delta > 0.1) {
		if (_currentFrame != _targetFrame) {
			if (_currentFrame < _targetFrame) {
				++_currentFrame;
			}
			else if (_currentFrame > _targetFrame) {
				--_currentFrame;
			}
		}
		getShape()->setTextureRect(sf::IntRect(_currentFrame * 33 + 1, (getID() - 1) * 18, 33, 16));
		_delta = 0;
	}
}