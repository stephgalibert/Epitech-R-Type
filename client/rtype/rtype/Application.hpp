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
#include "ApplicationState.hpp"

class Application
{
public:
	Application(void);
	~Application(void);

	void init(std::string host, std::string pwd);
	void loop(void);

private:
	void initNetwork(void);
	void initIcon(void);

	void inputMenu(InputHandler &input);
	void inputGame(InputHandler &input);

	void updateMenu(float delta);
	void updateGame(float delta);

	void drawMenu(sf::RenderWindow &window);
	void drawGame(sf::RenderWindow &window);

	bool isRunning(void) const;

private:
	TCPClient _client;
	Timer _timer;
	InputHandler _inputHandler;
	sf::RenderWindow _window;

	ApplicationState _state;
	FPSCounter _fps;
	MainMenuController _menu;
	GameController *_game;
	bool _quit;

  std::unordered_map<ApplicationState, std::function<void(InputHandler &)>, ApplicationStateHash > _inputs;
  std::unordered_map<ApplicationState, std::function<void(float)>, ApplicationStateHash > _updates;
  std::unordered_map<ApplicationState, std::function<void(sf::RenderWindow &)>, ApplicationStateHash > _draws;

	/* to remove later */
	std::string _host;
	std::string _pwd;
};

