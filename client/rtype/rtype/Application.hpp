#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "Timer.hpp"
#include "StaticTools.hpp"

#include "InputHandler.hpp"
#include "ProjectResource.hpp"
#include "MainMenu.hpp"
#include "Game.hpp"

#include "FPSCounter.hpp"


class Application
{
public:
	Application(void);
	~Application(void);

	/* Initialise l'application */
	void init(void);

	/* Boucle principale */
	void loop(void);

private:
	enum class State : short
	{
		ST_None = 0,
		ST_MainMenu = 1,
		ST_Game = 2
	};

private:
	Timer _timer;
	ProjectResource _resource;
	InputHandler _inputHandler;
	sf::RenderWindow _window;

	State _fsm;
	std::unordered_map<State, AController *> _controllers;

	FPSCounter _fps;
};

