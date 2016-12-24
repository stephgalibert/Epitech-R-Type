#pragma once

#include "ADrawable.hpp"
#include "StaticTools.hpp"

class Health : public ADrawable
{
private:
	static const float MAX_HEALTH;

	enum class State : uint8_t
	{
		HealthOn = 0,
		HealthOff = 1
	};

public:
	Health(void);
	virtual ~Health(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(IClient &client);

	void setHealth(uint8_t health);

private:
	void updateHealthOn(float delta);
	void updateHealthOff(float delta);

private:
	float _delta;
	float _deltaLife;
	bool _inverse;
	State _state;

	sf::ConvexShape *_shape;
	std::pair<short, short> _resolution;
	sf::Color _color;
	sf::Vector2f _initSize;
	sf::Vector2f _initPos;
	uint8_t _health;
};
