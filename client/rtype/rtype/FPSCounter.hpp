#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "StaticTools.hpp"
#include "ProjectResource.hpp"

class FPSCounter
{
public:
	FPSCounter(void);
	~FPSCounter(void);

	void init();
	void update(float delta);

	void draw(sf::RenderWindow &window);

private:
	sf::Text _text;
	float _delta;
	std::pair<short, short> _resolution;
};

