#pragma once

#include <SFML/Graphics.hpp>

#include "InputHandler.hpp"

class ALayout : public sf::Drawable, public sf::Transformable
{
public:
	ALayout(void);
	virtual ~ALayout(void);

	virtual void init(void) = 0;
	virtual bool input(InputHandler &input) = 0;
	virtual void update(float delta) = 0;
	virtual void recycle(void) = 0;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

