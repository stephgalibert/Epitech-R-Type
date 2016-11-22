#include "MainMenuController.hpp"

MainMenuController::MainMenuController()
	: _fsm(State::ST_Splash)
{
}

MainMenuController::~MainMenuController(void)
{
}

void MainMenuController::init(void)
{
	try {
		ProjectResource::TheProjectResource.getMusicByKey(ProjectResource::MAIN_THEME).play();
		//_splash.init();
		//_background.init();
	}
	catch (std::exception const& e) {
		throw (std::runtime_error(e.what()));
	}
}

bool MainMenuController::input(InputHandler &input)
{
	if (input.isKeyDown(sf::Keyboard::Key::Space)) {
		std::cout << "Spaaaaace" << std::endl;
	}
	return (false);
}

void MainMenuController::update(float delta)
{
	std::cout << "main menu update" << std::endl;

	/*if (!_splash.isFinished()) {
		_splash.update(delta);
	}
	else {
		//_background.update(delta);
	}*/
}

void MainMenuController::draw(sf::RenderWindow &window)
{
	/*if (!_splash.isFinished()) {
		_splash.draw(window);
	}
	else {
		//window.draw(_background);
	}*/
	//_world.display(window);
}

void MainMenuController::recycle(void)
{
	std::cout << "main menu recycle" << std::endl;
}