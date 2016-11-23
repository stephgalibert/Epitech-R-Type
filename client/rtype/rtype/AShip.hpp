#pragma once

#include "AMoveable.hpp"

#include "World.hpp"
#include "Explosion.hpp"

class AShip : public AMoveable
{
public:
	AShip(void);
	virtual ~AShip(void);

	virtual void init(void) = 0;
	virtual void update(float delta);
	virtual void destroy(void) = 0;

	void setTargetFrame(uint8_t targetFrame);
	void setCurrentFrame(uint8_t currentFrame);

	void shoot(void);

private:
	void updateFrame(void);

	float _delta;
	float _deltaLastShoot;
	uint8_t _targetFrame;
	uint8_t _currentFrame;
};

