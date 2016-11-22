#include "Application.hpp"

Application::Application(void)
{
	sf::Vector2i reso = StaticTools::GetResolution();

	sf::ContextSettings context;
	context.antialiasingLevel = 8;

	_window.create(sf::VideoMode(reso.x, reso.y), "R-Type", sf::Style::Default, context);
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

void Application::init(void)
{
	try {
		StaticTools::Log.open(".log", std::ios::out | std::ios::app);
		_fsm = State::ST_MainMenu;

		ProjectResource::TheProjectResource.load();
		_fps.init();

		_controllers[State::ST_MainMenu] = new MainMenuController();
		_controllers[State::ST_Game] = new GameController();
		
		_controllers.at(_fsm)->init();
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
		throw (std::runtime_error(e.what()));
	}

	_timer.restart();
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
				_window.close();
			}
		}

		_controllers.at(_fsm)->input(_inputHandler);

		_fps.update(delta);
		_controllers.at(_fsm)->update(delta);

		draw();
	}
}

void Application::draw(void)
{
	_window.clear();

	_controllers.at(_fsm)->draw(_window);
	_fps.draw(_window); // !

	_window.display();
}