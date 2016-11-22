#pragma once

#include <string>
#include <iostream>

#include "AController.hpp"
#include "Background.hpp"
#include "SplashScreen.hpp"

class MainMenuController : public AController
{
public:
	MainMenuController(void);
	virtual ~MainMenuController(void);

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
	//Background _background;
	//SplashScreen _splash;
	State _fsm;
};

