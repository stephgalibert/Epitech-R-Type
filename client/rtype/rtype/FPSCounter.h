#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

class FPSCounter
{
public:
	FPSCounter(void);
	~FPSCounter(void);

	void init(void);
	void update(float delta);

	void draw(sf::RenderWindow &window);

private:
	sf::Font _font;
	sf::Text _text;

	float _delta;
};

