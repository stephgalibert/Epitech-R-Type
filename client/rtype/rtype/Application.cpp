#include "Application.hpp"

Application::Application(std::string const& ip, std::string const& port)
	: _client(&_game, _menu, ip, port),
	  _menu(_client),
	  _ip(ip),
	  _port(port)
{
	std::pair<short, short> resolution = StaticTools::GetResolution();

	sf::ContextSettings context;
	context.antialiasingLevel = 4;

	_window.create(sf::VideoMode(resolution.first, resolution.second), "R-Type", sf::Style::Default, context);
	_window.setPosition(sf::Vector2i(0, 0));
	_window.setVerticalSyncEnabled(true);
	_window.setMouseCursorVisible(false);

	_state = ApplicationState::AS_MainMenu;
	_inputs[ApplicationState::AS_MainMenu] = std::bind(&Application::inputMenu, this, std::placeholders::_1);
	_inputs[ApplicationState::AS_Game] = std::bind(&Application::inputGame, this, std::placeholders::_1);
	_updates[ApplicationState::AS_MainMenu] = std::bind(&Application::updateMenu, this, std::placeholders::_1);
	_updates[ApplicationState::AS_Game] = std::bind(&Application::updateGame, this, std::placeholders::_1);
	_draws[ApplicationState::AS_MainMenu] = std::bind(&Application::drawMenu, this, std::placeholders::_1);
	_draws[ApplicationState::AS_Game] = std::bind(&Application::drawGame, this, std::placeholders::_1);

	_game = NULL;
	_quit = false;
}

Application::~Application(void)
{
	//if (_menu) {
	//	delete (_menu);
	//}
	//if (_client) {
	//	delete (_client);
	//}
}

void Application::init(std::string const& username, std::string const& host, std::string const& pwd)
{
	_username = username;
	_host = host;
	_pwd = pwd;
	try {
		ProjectResource::TheProjectResource.load();

		initIcon();
		initNetwork();
		
		_fps.init();
		_inputHandler.init();
		
		_menu.init();
		_menu.setHostIp(_ip);
		_menu.setPort(_port);

		if (!_username.empty()) {
			play();
		}
	}
	catch (std::exception const& e) {
		StaticTools::Log << "application: " << e.what() << std::endl;
		throw (std::runtime_error(e.what()));
	}

	_timer.restart();
}

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
			if (!isRunning()) {
				_client.disconnect();
				_window.close();
			}
		}

		_inputs.at(_state)(_inputHandler);
		_updates.at(_state)(delta);
		_draws.at(_state)(_window);
	}
}

void Application::initIcon(void)
{
	sf::Image image;

	if (!image.loadFromFile("./rsrc/sprites/icon.png")) {
		throw (std::runtime_error("can not load icon"));
	}
	_window.setIcon(128, 128, image.getPixelsPtr());
}

void Application::createGame(void)
{
	//MainMenuController::ConnectData const& data = _menu.getConnectData();

	//_username = data.username;
	//_host = data.game;
	//_pwd = data.password;

	//while (!_client.isConnected());
	_client.write(std::make_shared<CMDCreateParty>(_host, _pwd));
}

void Application::play(void)
{
	_menu.mute();
	_state = ApplicationState::AS_Game;
	_game = new GameController(_client);
	_game->init();
	_game->connectToParty(_username, _host, _pwd);
}

void Application::initNetwork(void)
{
	_client.connect();
	_client.run();
}

void Application::inputMenu(InputHandler &input)
{
	_menu.input(input);
}

void Application::inputGame(InputHandler &input)
{
	_game->input(input);
}

void Application::updateMenu(float delta)
{
	_fps.update(delta);
	_menu.update(delta);

	switch (_menu.pullAction()) {
	case MainMenuController::SelectedAction::CREATE:
		_host = _menu.getConnectData().game;
		_pwd = _menu.getConnectData().password;
		_username = _menu.getConnectData().username;
		createGame();
	case MainMenuController::SelectedAction::PLAY:
		_host = _menu.getConnectData().game;
		_pwd = _menu.getConnectData().password;
		_username = _menu.getConnectData().username;
		play();
		break;
	case MainMenuController::SelectedAction::OPTIONS:
		//_client.setRemote(_menu.getConnectData().hostIp, _menu.getConnectData().port);
		break;
	case MainMenuController::SelectedAction::QUIT:
		_quit = true;
		break;
	default:
		break;
	}

	/*
	// TEST:
	while (!_client.isConnected());
	_client.write(std::make_shared<CMDCreateParty>(_host, _pwd));

	_menu.mute();
	_state = ApplicationState::AS_Game;
	_game = new GameController(_client);
	_game->init();
	_game->connectToParty(_username, _host, _pwd);*/
}

void Application::updateGame(float delta)
{
	_fps.update(delta);
	_game->update(delta);

	if (_game->gameFinished()) {
		_state = ApplicationState::AS_MainMenu;
		_menu.restartMusic();
		delete (_game);
		_game = NULL;
	}
}

void Application::drawMenu(sf::RenderWindow &window)
{
	_window.clear();
	_menu.draw(window);
	_fps.draw(_window);
	_window.display();
}

void Application::drawGame(sf::RenderWindow &window)
{
	_window.clear();
	_game->draw(window);
	_fps.draw(_window);
	_window.display();
}

bool Application::isRunning(void) const
{
	return (!_inputHandler.isExiting() && !_quit && _window.isOpen());
}