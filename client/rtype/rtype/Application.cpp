#include "Application.hpp"

Application::Application(void)
	: _client("127.0.0.1", "4242")
{
	sf::Vector2i reso(800, 480);

	sf::ContextSettings context;
	context.antialiasingLevel = 8;

	_window.create(sf::VideoMode(reso.x, reso.y), "R-Type", sf::Style::Close, context);
	_window.setPosition(sf::Vector2i(0, 0));
	_window.setVerticalSyncEnabled(true);
}

Application::~Application(void)
{
	for (auto it : _controllers) {
		it.second->recycle();
		delete (it.second);
	}
}

#include <Windows.h> // !
void Application::init(std::string host, std::string pwd)
{
	try {
		StaticTools::Log.open("client" + std::to_string(GetCurrentProcessId()) + ".log", std::ios::out | std::ios::app);

		_client.connect();
		_client.run();

		_fsm = State::ST_Game;

		ProjectResource::TheProjectResource.load();
		_fps.init();
		_inputHandler.init();

		GameController *game = new GameController(_client, "name", "pwd");
		_client.setGameController(game);

		_controllers[(int)State::ST_MainMenu] = new MainMenuController();
		_controllers[(int)State::ST_Game] = game;
		
		_controllers.at((int)_fsm)->init();
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
		throw (std::runtime_error(e.what()));
	}

	_timer.restart();
}

void Application::setState(State state)
{
	switch (state)
	{
	case State::ST_MainMenu:
		st_main_menu();
		break;
	case State::ST_Game:
		st_game();
		break;
	}
	//_client.setGameController(_controllers[(int)_fsm]);
}
// les états peuvent se changer d'eux même => à faire
void Application::loop(void)
{
	sf::Event event;
	float delta = 0;

	while (_window.isOpen())
	{
		delta = _timer.restart();

		while (_window.pollEvent(event))
		{
			_inputHandler.OnEvent(event);
			if (_inputHandler.isExiting()) {
				_client.disconnect();
				_window.close();
			}
		}

		_controllers.at((int)_fsm)->input(_inputHandler);
		_fps.update(delta);
		_controllers.at((int)_fsm)->update(delta);

		draw();
	}
}


void Application::st_main_menu(void)
{
	_fsm = State::ST_MainMenu;
}

void Application::st_game(void)
{
	_fsm = State::ST_Game;
}

void Application::draw(void)
{
	_window.clear();

	_controllers.at((int)_fsm)->draw(_window);
	_fps.draw(_window); // !

	_window.display();
}
