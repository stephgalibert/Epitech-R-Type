#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "Timer.hpp"
#include "StaticTools.hpp"

#include "InputHandler.hpp"
#include "ProjectResource.hpp"
#include "MainMenuController.hpp"
#include "GameController.hpp"
#include "UDPClient.hpp"
#include "TCPClient.hpp"

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
	void draw(void);

	UDPClient _client;
	Timer _timer;
	InputHandler _inputHandler;
	sf::RenderWindow _window;

	State _fsm;
	std::unordered_map<int, AController *> _controllers;

	FPSCounter _fps; // tmp
};

