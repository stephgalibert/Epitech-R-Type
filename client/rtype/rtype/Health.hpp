#pragma once

#include "ADrawable.hpp"
#include "StaticTools.hpp"

class Health : public ADrawable
{
private:
	static const float MAX_HEALTH;

public:
	Health(void);
	virtual ~Health(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(void);

	void setHealth(uint8_t health);

private:
	float _delta;
	sf::ConvexShape *_shape;
	std::pair<short, short> _resolution;
	sf::Vector2f _initSize;
	sf::Vector2f _initPos;
};

