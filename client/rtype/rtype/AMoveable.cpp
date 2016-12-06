#include "AMoveable.hpp"

AMoveable::AMoveable(void)
{
}

AMoveable::~AMoveable(void)
{
}

void AMoveable::move(float delta)
{
	if (getAngle() != -1) {
		
		float x = std::cos(getRadians()) * getVelocity() * delta;
		float y = std::sin(getRadians()) * getVelocity() * delta;

		ADrawable::move(x, y);
	}
}