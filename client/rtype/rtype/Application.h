#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Chrono.h"
#include "SplashScreen.h"
#include "FPSCounter.h"

class Application
{
public:
	Application(void);
	~Application(void);

	void init(void);
	void loop(void);

private:
	void draw(void);

	sf::ContextSettings _cx;
	sf::RenderWindow _window;

	Tools::Chronometer _timer;

	SplashScreen _splash;
	FPSCounter _fps;
};

