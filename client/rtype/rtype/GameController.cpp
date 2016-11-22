#include "GameController.hpp"

GameController::GameController()
{
}

GameController::~GameController(void)
{
	recycle();
}

void GameController::init(void)
{
	LevelResource::TheLevelResource.load();
	World::TheWorld.init();

	//LevelResource::TheLevelResource.getMusicByKey("stage_01").play();
	_player = World::TheWorld.spawnEntity<Player>();
	_bg.init();
}

bool GameController::input(InputHandler &input)
{
	_player->input(input);
	return (false);

}
void GameController::update(float delta)
{
	_bg.update(delta);
	World::TheWorld.update(delta);
}

void GameController::draw(sf::RenderWindow &window)
{
	window.draw(_bg);
	World::TheWorld.display(window);
}

void GameController::recycle(void)
{
	World::TheWorld.recycle();
}