#include "GameController.hpp"

GameController::GameController(IClient &network)
	: _network(network),
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
	World::init(&_network);

	//LevelResource::TheLevelResource.getMusicByKey("stage_01").play();

	_loading.init();
	_loading.setBaseText("Waiting players");

	_back.init();
	_front.init();
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

	if (!isReady()) {
		_loading.update(delta);
	} else {
		World::update(delta);
	}
}

void GameController::draw(sf::RenderWindow &window)
{
	_back.draw(window);
	_front.draw(window);

	if (!isReady()) {
		_loading.draw(window);
	}
	else {
		World::display(window);
	}
}

void GameController::recycle(void)
{
	World::recycle();
}

void GameController::connectToParty(std::string const& partyName, std::string const& pwd)
{
	_partyName = partyName;
	_partyPwd = pwd;

	if (_network.isConnected()) {
		_network.write(std::make_shared<CMDCreateParty>(_partyName, _partyPwd));
		_network.write(std::make_shared<CMDConnect>(_partyName, _partyPwd));
	}
}

void GameController::setReady(bool value)
{
	_ready = value;
}

void GameController::setPlayer(Player *player)
{
	_player = player;
}

bool GameController::isReady(void) const
{
	return (_ready);
}