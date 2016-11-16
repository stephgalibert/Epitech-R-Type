#include "Application.hpp"

Application::Application(void)
{
	sf::ContextSettings context;
	context.antialiasingLevel = 8;

	_window.create(sf::VideoMode(1920, 1080), "R-Type", sf::Style::Default, context);
	_window.setVerticalSyncEnabled(true);
}

Application::~Application(void)
{
}

void Application::init(void)
{
	try {
		StaticTools::Log.open(".log", std::ios::out | std::ios::app);
		ProjectResource::Load();

		_splash.init();
		_fps.init();
		ProjectResource::Musics.play("main_theme");
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
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
			switch (event.type)
			{
			case sf::Event::Closed:
				_window.close();
				break;
			}
		}

		_splash.update(delta);
		_fps.update(delta);

		draw();
	}

}

void Application::draw(void)
{
	_window.clear();
	_splash.draw(_window);
	_fps.draw(_window);
	_window.display();
}