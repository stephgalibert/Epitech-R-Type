#pragma once

#include <string>
#include <iostream>

#include "World.hpp"
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
	enum class State : short
	{
		ST_None = 0,
		ST_Splash = 1,
		ST_Menu = 2
	};

private:
	World _world;
	Background _background;
	SplashScreen _splash;
	State _fsm;
};

