#pragma once

#include "ADrawable.hpp"

class ACollidable : public ADrawable
{
public:
	ACollidable();
	virtual ~ACollidable();

	bool isCollidingWith(ACollidable *other);
	sf::FloatRect getBoundingBox(void) const;
};

