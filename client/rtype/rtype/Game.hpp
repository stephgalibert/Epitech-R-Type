#pragma once

#include <iostream>
#include <string>

#include "AController.hpp"

class Game : public AController
{
public:
	Game(ProjectResource &resource);
	virtual ~Game(void);

	virtual void init(void);
	virtual bool input(InputHandler &input);
	virtual void update(float delta);
	virtual void draw(sf::RenderWindow &window);
	virtual void recycle(void);

private:

};

