#include "GameController.hpp"

GameController::GameController(IClient &network)
	: _network(network),
	  _player(NULL),
	  _back("background", 0.03f),
	  _front("background2", 0.01f)
{
	//for (size_t i = 0; i < 3; ++i) {
	//	_mates[i] = NULL;
	//}
	_state = GameStatusType::Waiting;
}

GameController::~GameController(void)
{
	recycle();
}

void GameController::init(void)
{
	LevelResource::TheLevelResource.load();
	World::init(&_player, &_network);

	//LevelResource::TheLevelResource.getMusicByKey("stage_01").play();

	_loading.init();
	_loading.setBaseText("Waiting players");

	_connectionLost.init();
	_connectionLost.setBaseText("Connection lost :/");

	_hud.init();

	_back.init();
	_front.init();
}

bool GameController::input(InputHandler &input)
{
	if (_player) {
		_player->input(input);
	}
	_hud.input(input);
	return (false);
}
void GameController::update(float delta)
{
	switch (_state)
	{
	case GameStatusType::Waiting:
		updateWaiting(delta);
		break;
	case GameStatusType::Playing:
		updatePlaying(delta);
		break;
	case GameStatusType::GameOver:
		updateGameOver(delta);
		break;
	case GameStatusType::GameWin:
		updateGameWin(delta);
		break;
	default:
		break;
	}
}

void GameController::draw(sf::RenderWindow &window)
{
	switch (_state)
	{
	case GameStatusType::Waiting:
		drawWaiting(window);
		break;
	case GameStatusType::Playing:
		drawPlaying(window);
		break;
	case GameStatusType::GameOver:
		drawGameOver(window);
		break;
	case GameStatusType::GameWin:
		drawGameWin(window);
		break;
	default:
		break;
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
	_player->setHUD(&_hud);
	_hud.setColor(_player->getID());
}

void GameController::setGameStatus(GameStatusType status)
{
	_state = status;
}

//void GameController::addMate(Mate *mate)
//{
//	size_t i = 0;
//
//	while (i < 3 && !_mates[i]) {
//		++i;
//	}
//	if (i < 3 && _mates[i]) {
//		_mates[i] = mate;
//	}
//}

Player *GameController::getPlayer(void) const
{
	return (_player);
}

bool GameController::isReady(void) const
{
	return (_ready);
}

void GameController::updateWaiting(float delta)
{
	_back.update(delta);
	_front.update(delta);
	_loading.update(delta);
}

void GameController::updatePlaying(float delta)
{
	_back.update(delta);
	_front.update(delta);

	//if (!isReady()) {
	//	_loading.update(delta);
	//}
	//else {
	World::update(delta);
	if (!_network.isConnected()) {
		_connectionLost.update(delta);
	}
	//}
	_hud.update(delta);
}

void GameController::updateGameOver(float delta)
{
	_back.update(delta);
	_front.update(delta);
	if (_player) {
		_player = NULL;
		World::recycle();
	}
}

void GameController::updateGameWin(float delta)
{
	_back.update(delta);
	_front.update(delta);
	if (_player) {
		_player = NULL;
		World::recycle();
	}
}


void GameController::drawWaiting(sf::RenderWindow &window)
{
	_back.draw(window);
	_front.draw(window);

	_loading.draw(window);

	_hud.draw(window);
}

void GameController::drawPlaying(sf::RenderWindow &window)
{
	_back.draw(window);
	_front.draw(window);

	//if (!isReady()) {
	//	_loading.draw(window);
	//}
	//else {
	World::display(window);
	if (!_network.isConnected()) {
		_connectionLost.draw(window);
	}
	//}
	_hud.draw(window);
}

void GameController::drawGameOver(sf::RenderWindow &window)
{
	_back.draw(window);
	_front.draw(window);

	_loading.draw(window);

	_hud.draw(window);
}

void GameController::drawGameWin(sf::RenderWindow &window)
{
	_back.draw(window);
	_front.draw(window);

	_loading.draw(window);

	_hud.draw(window);
}