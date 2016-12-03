#include "GameController.hpp"

GameController::GameController(IClient &network, std::string const& partyName, std::string const& partyPwd)
	: _network(network),
	  _partyName(partyName),
	  _partyPwd(partyPwd),
	  _player(NULL),
	  _back("background", 0.03f),
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
	_back.init();
	_front.init();

	while (!_network.isConnected());
	_network.write(std::make_shared<CMDCreateParty>(_partyName, _partyPwd));
	_network.write(std::make_shared<CMDConnect>(_partyName, _partyPwd));
}

bool GameController::input(InputHandler &input)
{
	if (_player) {
		_player->input(input);
	}
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

void GameController::addPlayer(Player *player)
{
	_player = player;
}