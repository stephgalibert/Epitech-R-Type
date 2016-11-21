#pragma once

#include <string>
#include <iostream>

#include "AController.hpp"
#include "Background.hpp"
#include "SplashScreen.hpp"

class MainMenu : public AController
{
public:
	MainMenu(ProjectResource &resource);
	virtual ~MainMenu(void);

	virtual void init(void);
	virtual bool input(InputHandler &input);
	virtual void update(float delta);
	virtual void draw(sf::RenderWindow &window);
	virtual void recycle(void);

private:
	Background _background;
	SplashScreen _splash;
};

