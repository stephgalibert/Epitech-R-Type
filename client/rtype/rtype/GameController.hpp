#pragma once

#include <iostream>
#include <string>

#include "World.hpp"
#include "AController.hpp"

#include "Background.hpp"
#include "Player.hpp"
#include "Mate.hpp"

#include "IClient.hpp"
#include "CMDConnect.hpp"

#include "HUDController.hpp"
#include "LoadingController.hpp"
#include "ConnectionLostController.hpp"
#include "GameOverController.hpp"
#include "GameWinController.hpp"
#include "ScoreController.hpp"
#include "BossIncomingController.hpp"

#include "MessageLayout.hpp"
#include "EscapeLayout.hpp"

class GameController : public AController
{
public:
	GameController(IClient &network);
	virtual ~GameController(void);

	virtual void init(void);
	virtual bool input(InputHandler &input);
	virtual void update(float delta);
	virtual void draw(sf::RenderWindow &window);
	virtual void recycle(void);

	void connectToParty(std::string const& username, std::string const& partyName, std::string const& pwd);
	void displayMessage(std::string const& msg);

	void setReady(bool value);
	void setPlayer(Player *player);
	void setGameStatus(GameStatusType status);
	void addMate(Mate *mate);
	void removeMate(uint16_t id);

	Player *getPlayer(void) const;
	bool isReady(void) const;

	bool gameFinished(void) const;

private:
	bool inputWaiting(InputHandler &input);
	bool inputPlaying(InputHandler &input);
	bool inputGameOver(InputHandler &input);
	bool inputGameWin(InputHandler &input);

	void updateWaiting(float delta);
	void updatePlaying(float delta);
	void updateGameOver(float delta);
	void updateGameWin(float delta);
	void updateBossIncoming(float delta);

	void drawWaiting(sf::RenderWindow &window);
	void drawPlaying(sf::RenderWindow &window);
	void drawGameOver(sf::RenderWindow &window);
	void drawGameWin(sf::RenderWindow &window);
	void drawBossIncoming(sf::RenderWindow &window);

	//void reset(void);

	LoadingController _loading;
	ConnectionLostController _connectionLost;
	GameOverController _gameOver;
	GameWinController _gameWin;
	HUDController _hud;
	ScoreController _scoreController;
	BossIncomingController _bossIncoming;
	MessageLayout _messageLayout;
	EscapeLayout _escapeLayout;

	IClient &_network;
	std::string _username;
	std::string _partyName;
	std::string _partyPwd;
	Player *_player;
	Mate *_mates[3];
	Background _back;
	Background _front;
	bool _ready;
	bool _gameFinished;
	GameStatusType _state;

	//bool _gameStarted;
	//bool _gameStateChanged;
	GameStatusType _prevState;
};

