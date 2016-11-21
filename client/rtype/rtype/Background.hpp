#pragma once

#include <SFML\Graphics.hpp>

#include "ADrawable.hpp"
#include "StaticTools.hpp"

class Background : public ADrawable
{
public:
	Background(ProjectResource &resource);
	virtual ~Background(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(void);

private:
	float _delta;
	float _test;
	sf::Vector2i _resolution;
	sf::Vector2i _offset;
};

