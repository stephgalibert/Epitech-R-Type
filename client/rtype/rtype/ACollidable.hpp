#pragma once

#include "ADrawable.hpp"

class ACollidable : public ADrawable
{
public:
	ACollidable();
	virtual ~ACollidable();

	virtual void init(void) = 0;
	virtual void update(float delta) = 0;
	virtual void destroy(void) = 0;

	bool isCollidingWith(ACollidable *other);
	sf::FloatRect getBoundingBox(void) const;
};

