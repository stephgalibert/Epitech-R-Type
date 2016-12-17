#pragma once

#include "ADrawable.hpp"

class LoadedShotLayout : public ADrawable
{
private:
	enum class State : uint8_t
	{
		Normal = 0,
		Max = 1
	};

public:
	static const int MAX_LOAD_SHOT = 1800;

public:
	LoadedShotLayout(void);
	virtual ~LoadedShotLayout(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(void);

	void setLoadedShot(float time);

private:
	void updateNormal(float delta);
	void updateMax(float delta);

private:
	float _delta;
	sf::ConvexShape *_shape;
	sf::Color _color;
	sf::Vector2f _initSize;
	sf::Vector2f _initPos;
	bool _inverse;
	bool _max;
	float _deltaShot;
	State _state;
};

