#pragma once

#include "ADestroyable.hpp"

class AMoveable : public ADestroyable
{
public:
	AMoveable();
	virtual ~AMoveable();

	virtual void init(void) = 0;
	virtual void update(float delta) = 0;
	virtual void destroy(void) = 0;

	void move(float delta);

	void setVelocity(float velocity);
	float getVelocity(void) const;

	void setAngle(float angle);
	float getAngle(void) const;

private:
	float _velocity;
	float _degrees;
	float _radians;
};

