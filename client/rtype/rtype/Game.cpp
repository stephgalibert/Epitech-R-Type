#include "Game.hpp"

Game::Game(ProjectResource &resource)
	: AController(resource)
{
}

Game::~Game(void)
{
}

void Game::init(void)
{

}

bool Game::input(InputHandler &input)
{
	(void)input;
	return (false);

}
void Game::update(float delta)
{
	(void)delta;
	std::cout << "game update" << std::endl;
}

void Game::draw(sf::RenderWindow &window)
{
	(void)window;
}

void Game::recycle(void)
{
	std::cout << "game recycle" << std::endl;
}