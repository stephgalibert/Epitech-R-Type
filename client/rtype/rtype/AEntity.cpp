#include "AEntity.hpp"

AEntity::AEntity()
	  : _velocity(0),
		_degrees(0),
		_radians(0),
	   _direction(0)
{
}

AEntity::~AEntity(void)
{
}

void AEntity::setID(uint8_t id)
{
	_id = id;
}

uint8_t AEntity::getID(void) const
{
	return (_id);
}

void AEntity::setDirection(uint8_t direction)
{
	setAngle(-1);
	if (direction & NORTH) {
		setAngle(-90.f);
	}
	else if (direction & SOUTH) {
		setAngle(90.f);
	}

	if (direction & EAST) {
		setAngle(getAngle() / 2.f);
	}
	else if (direction & WEAST) {
		setAngle(-180.f - getAngle() / 2.f);
	}
	_direction = direction;
}

uint8_t AEntity::getDirection(void) const
{
	return (_direction);
}

void AEntity::move(float delta)
{
	if (_degrees != -1) {
		ADrawable::move(std::cos(_radians) * _velocity * delta,
			std::sin(_radians) * _velocity * delta);
	}
}

void AEntity::setVelocity(float velocity)
{
	_velocity = velocity;
}

float AEntity::getVelocity(void) const
{
	return (_velocity);
}

void AEntity::setAngle(float angle)
{
	_degrees = angle;
	_radians = angle * (2.f * 3.14159265f) / 360.f;
}

float AEntity::getAngle(void) const
{
	return (_degrees);
}