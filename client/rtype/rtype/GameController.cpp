#include "GameController.hpp"

GameController::GameController(IClient &network)
	: _scoreController(&_player, &_mates[0]),
	  _network(network),
	  _player(NULL),
	  _back("background", 0.03f),
	  _front("background2", 0.01f)
{
	for (size_t i = 0; i < 3; ++i) {
		_mates[i] = NULL;
	}
	_state = GameStatusType::Waiting;
	_gameFinished = false;
	_prevState = GameStatusType::None;
}

GameController::~GameController(void)
{
	recycle();
}

void GameController::init(void)
{
	World::init(&_player, &_network);

	try {
		_loading.init();
		_loading.setBaseText("Waiting for players");

		_connectionLost.init();
		_connectionLost.setBaseText("Connection lost :/");

		_gameOver.init();
		_gameWin.init();
		_hud.init();
		_scoreController.init();
		_back.init();
		_front.init();
		_messageLayout.init();
		_escapeLayout.init();
		_bossIncoming.init();

		_scoreController.setColor(sf::Color(255, 255, 224));
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
	}
}

bool GameController::input(InputHandler &input)
{
	bool ret = false;

	switch (_state)
	{
	case GameStatusType::Waiting:
		ret = inputWaiting(input);
		break;
	case GameStatusType::BossIncoming:
	case GameStatusType::Playing:
		ret = inputPlaying(input);
		break;
	case GameStatusType::GameOver:
		ret = inputGameOver(input);
		break;
	case GameStatusType::GameWin:
		ret = inputGameWin(input);
		break;
	default:
		break;
	}

	return (ret);
}
void GameController::update(float delta)
{
	switch (_state)
	{
	case GameStatusType::Waiting:
		updateWaiting(delta);
		break;
	case GameStatusType::BossIncoming:
		updateBossIncoming(delta);
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
	case GameStatusType::BossIncoming:
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
	ProjectResource::TheProjectResource.getMusicByKey("stage_01").stop();
}

void GameController::connectToParty(std::string const& username, std::string const& partyName, std::string const& pwd)
{
	_username = username;
	_partyName = partyName;
	_partyPwd = pwd;
	_network.write(std::make_shared<CMDConnect>(_username, _partyName, _partyPwd));
}

void GameController::displayMessage(std::string const& msg)
{
	_messageLayout.addMessage(msg);
}

void GameController::setReady(bool value)
{
	_ready = value;
}

void GameController::setPlayer(Player *player)
{
	if (player) {
		_player = player;
		_player->setHUD(&_hud);
		_hud.setColor(_player->getID());
	}
}

void GameController::setGameStatus(GameStatusType status)
{
	_state = status;
}

void GameController::addMate(Mate *mate)
{
	size_t i = 0;

	while (i < 3 && _mates[i]) {
		++i;
	}
	if (i < 3 && !_mates[i]) {
		_mates[i] = mate;
	}
}

void GameController::removeMate(uint16_t id)
{
	for (size_t i = 0; i < 3; ++i) {
		if (_mates[i] && _mates[i]->getID() == id) {
			_mates[i] = NULL;
		}
	}
}

Player *GameController::getPlayer(void) const
{
	return (_player);
}

bool GameController::isReady(void) const
{
	return (_ready);
}

bool GameController::gameFinished(void) const
{
	return (_gameFinished);
}

bool GameController::inputWaiting(InputHandler &input)
{
	_messageLayout.input(input);
	_escapeLayout.input(input);
	return (false);
}

bool GameController::inputPlaying(InputHandler &input)
{
	if (_player && !_escapeLayout.isVisible()) {
		_player->input(input);
		_hud.input(input);
	}

	_scoreController.input(input);
	_messageLayout.input(input);
	_escapeLayout.input(input);
	return (false);
}

bool GameController::inputGameOver(InputHandler &input)
{
	_messageLayout.input(input);
	return (false);
}

bool GameController::inputGameWin(InputHandler &input)
{
	_messageLayout.input(input);
	return (false);
}

void GameController::updateWaiting(float delta)
{
	_back.update(delta);
	_front.update(delta);
	_loading.update(delta);
	_escapeLayout.update(delta);
	if (_escapeLayout.exit()) {
		_network.write(std::make_shared<CMDDisconnect>());
		_gameFinished = true;
	}
	_messageLayout.update(delta);
}

void GameController::updatePlaying(float delta)
{
	if (_prevState != _state && _state != GameStatusType::BossIncoming) {
		ProjectResource::TheProjectResource.getMusicByKey("stage_01").setVolume(StaticTools::musicVolume);
		ProjectResource::TheProjectResource.getMusicByKey("stage_01").setLoop(true);
		ProjectResource::TheProjectResource.getMusicByKey("stage_01").play();
		_prevState = _state;
	}

	_back.update(delta);
	_front.update(delta);

	World::update(delta);

	if (!_network.isConnected()) {
		_connectionLost.update(delta);
	}

	if (_player) {
		_hud.update(delta);
	}

	_escapeLayout.update(delta);
	if (_escapeLayout.exit()) {
		_network.write(std::make_shared<CMDDisconnect>());
		_gameFinished = true;
	}

	_scoreController.update(delta);
	_messageLayout.update(delta);
}

void GameController::updateGameOver(float delta)
{
	if (_prevState != _state) {
		ProjectResource::TheProjectResource.getMusicByKey("stage_01").stop();
		ProjectResource::TheProjectResource.getMusicByKey("boss_incoming").stop();
		_scoreController.setVisible(true);
		_scoreController.setMarginTop(80);
		_prevState = _state;
	}

	_gameOver.update(delta);
	if (_gameOver.hasFinished()) {
		_gameFinished = true;
	}
	_scoreController.update(delta);
	_messageLayout.update(delta);
}

void GameController::updateGameWin(float delta)
{
	if (_prevState != _state) {
		ProjectResource::TheProjectResource.getMusicByKey("stage_01").stop();
		ProjectResource::TheProjectResource.getMusicByKey("boss_incoming").stop();
		_scoreController.setVisible(true);
		_scoreController.setMarginTop(80);
		_prevState = _state;
	}

	_gameWin.update(delta);
	if (_gameWin.hasFinished()) {
		_gameFinished = true;
	}
	_scoreController.update(delta);
	_messageLayout.update(delta);
}

void GameController::updateBossIncoming(float delta)
{
	_bossIncoming.update(delta);
	if (_bossIncoming.hasFinished()) {
		setGameStatus(GameStatusType::Playing);
	}
}

void GameController::drawWaiting(sf::RenderWindow &window)
{
	_back.draw(window);
	_front.draw(window);

	_loading.draw(window);

	if (_player) {
		_hud.draw(window);
	}
	window.draw(_messageLayout);
	window.draw(_escapeLayout);
}

void GameController::drawPlaying(sf::RenderWindow &window)
{
	_back.draw(window);
	_front.draw(window);

	World::display(window);
	if (!_network.isConnected()) {
		_connectionLost.draw(window);
	}
	if (_player) {
		_hud.draw(window);
	}

	_scoreController.draw(window);
	window.draw(_messageLayout);
	window.draw(_escapeLayout);

	if (_state == GameStatusType::BossIncoming) {
		drawBossIncoming(window);
	}
}

void GameController::drawGameOver(sf::RenderWindow &window)
{
	_back.draw(window);
	_front.draw(window);

	if (_player) {
		_hud.draw(window);
	}

	window.draw(_messageLayout);
	_gameOver.draw(window);
	_scoreController.draw(window);
}

void GameController::drawGameWin(sf::RenderWindow &window)
{
	_back.draw(window);
	_front.draw(window);

	World::display(window);

	if(_player) {
		_hud.draw(window);
	}

	window.draw(_messageLayout);
	_gameWin.draw(window);
	_scoreController.draw(window);
}

void GameController::drawBossIncoming(sf::RenderWindow &window)
{
	_bossIncoming.draw(window);
}