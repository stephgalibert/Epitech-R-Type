#include "GameController.hpp"

GameController::GameController()
{
}

GameController::~GameController(void)
{
}

void GameController::init(void)
{

}

bool GameController::input(InputHandler &input)
{
	(void)input;
	return (false);

}
void GameController::update(float delta)
{
	(void)delta;
	std::cout << "game update" << std::endl;
}

void GameController::draw(sf::RenderWindow &window)
{
	(void)window;
}

void GameController::recycle(void)
{
	std::cout << "game recycle" << std::endl;
}