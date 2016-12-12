#pragma once

#include "ADrawable.hpp"

class LoadedShotLayout : public ADrawable
{
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
	float _delta;
	sf::ConvexShape *_shape;
	sf::Vector2f _initSize;
	sf::Vector2f _initPos;
	bool _decrease;
	float _deltaShot;
};

