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

#include "EnumHash.hpp"

class Application
{
public:
	Application(std::string const& ip, std::string const& port);
	~Application(void);

	void init(std::string const& username, std::string const& host, std::string const& pwd); // todo delete the params
	void loop(void);

private:
	void initNetwork(void);
	void initIcon(void);

	void createGame(void);
	void play(void);

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

	std::unordered_map<ApplicationState, std::function<void(InputHandler &)>, EnumHash> _inputs;
	std::unordered_map<ApplicationState, std::function<void(float)>, EnumHash> _updates;
	std::unordered_map<ApplicationState, std::function<void(sf::RenderWindow &)>, EnumHash> _draws;

	std::string _ip;
	std::string _port;

	/* to remove later */
	std::string _username;
	std::string _host;
	std::string _pwd;
};

