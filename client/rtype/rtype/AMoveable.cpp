#include "AMoveable.hpp"

AMoveable::AMoveable(void)
	: _velocity(0),
	  _degrees(0),
	  _radians(0)
{
}

AMoveable::~AMoveable(void)
{
}

void AMoveable::move(float delta)
{
	if (_degrees != -1) {
		ADestroyable::move(std::cos(_radians) * _velocity * delta,
			std::sin(_radians) * _velocity * delta);
	}
}

void AMoveable::setVelocity(float velocity)
{
	_velocity = velocity;
}

float AMoveable::getVelocity(void) const
{
	return (_velocity);
}

void AMoveable::setAngle(float angle)
{
	_degrees = angle;
	_radians = angle * (2.f * 3.14159265f) / 360.f;
}

float AMoveable::getAngle(void) const
{
	return (_degrees);
}
