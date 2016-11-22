#include "AMoveable.hpp"

AMoveable::AMoveable(void)
	: _velocity(0),
	  _angle(0)
{
}

AMoveable::~AMoveable(void)
{
}

void AMoveable::move(void)
{
	if (_angle != -1) {
		ADestroyable::move(std::cosf(_angle * (2.f * 3.14159265f) / 360.f) * _velocity,
			std::sinf(_angle * (2.f * 3.14159265f) / 360.f) * _velocity);
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
	_angle = angle;
}

float AMoveable::getAngle(void) const
{
	return (_angle);
}