#include "MainMenu.hpp"

MainMenu::MainMenu(ProjectResource &resource)
	: AController(resource)
{
}

MainMenu::~MainMenu(void)
{
}

void MainMenu::init(void)
{
	try {
		sf::Music &music = getProjectResource().getMusicByKey(ProjectResource::MAIN_THEME);
		music.play();
		_splash.init();
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
	_splash.update(delta);
}

void MainMenu::draw(sf::RenderWindow &window)
{
	_splash.draw(window);
}

void MainMenu::recycle(void)
{
	std::cout << "main menu recycle" << std::endl;
}