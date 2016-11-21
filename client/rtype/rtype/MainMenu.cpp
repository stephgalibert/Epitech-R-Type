#include "MainMenu.hpp"

MainMenu::MainMenu(ProjectResource &resource)
	: AController(resource),
	  _world(resource),
	  _background(resource),
	  _fsm(State::ST_Splash)
{
}

MainMenu::~MainMenu(void)
{
}

void MainMenu::init(void)
{
	try {
		getProjectResource().getMusicByKey(ProjectResource::MAIN_THEME).play();
		_splash.init();
		_background.init();
	}
	catch (std::exception const& e) {
		throw (std::runtime_error(e.what()));
	}
}

bool MainMenu::input(InputHandler &input)
{
	if (input.isKeyDown(sf::Keyboard::Key::Space)) {
		std::cout << "Spaaaaace" << std::endl;
	}
	return (false);
}

void MainMenu::update(float delta)
{
	std::cout << "main menu update" << std::endl;

	if (!_splash.isFinished()) {
		_splash.update(delta);
	}
	else {
		_background.update(delta);
	}
}

void MainMenu::draw(sf::RenderWindow &window)
{
	if (!_splash.isFinished()) {
		_splash.draw(window);
	}
	else {
		window.draw(_background);
	}
	//_world.display(window);
}

void MainMenu::recycle(void)
{
	std::cout << "main menu recycle" << std::endl;
}