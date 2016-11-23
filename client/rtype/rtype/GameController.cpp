#include "GameController.hpp"

GameController::GameController()
	: _back("background", 0.03f),
	  _front("background2", 0.01f)
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
	_back.init();
	_front.init();
}

bool GameController::input(InputHandler &input)
{
	_player->input(input);
	return (false);

}
void GameController::update(float delta)
{
	_back.update(delta);
	_front.update(delta);
	World::TheWorld.update(delta);
}

void GameController::draw(sf::RenderWindow &window)
{
	_back.draw(window);
	_front.draw(window);
	World::TheWorld.display(window);
}

void GameController::recycle(void)
{
	World::TheWorld.recycle();
}