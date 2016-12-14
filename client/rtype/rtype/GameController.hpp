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
#include "ScoreController.hpp"
#include "MessageLayout.hpp"

class GameController : public AController
{
private:
	enum class State : uint8_t
	{
		Waiting = 0,
		Playing = 1,
		GameOver = 2,
		GameWin = 3
	};

public:
	GameController(IClient &network);
	virtual ~GameController(void);

	virtual void init(void);
	virtual bool input(InputHandler &input);
	virtual void update(float delta);
	virtual void draw(sf::RenderWindow &window);
	virtual void recycle(void);

	void connectToParty(std::string const& partyName, std::string const& pwd);
	void displayMessage(std::string const& msg);

	void setReady(bool value);
	void setPlayer(Player *player);
	void setGameStatus(GameStatusType status);
	void addMate(Mate *mate);
	void removeMate(uint16_t id);

	Player *getPlayer(void) const;
	bool isReady(void) const;

private:
	bool inputWaiting(InputHandler &input);
	bool inputPlaying(InputHandler &input);
	bool inputGameOver(InputHandler &input);
	bool inputGameWin(InputHandler &input);

	void updateWaiting(float delta);
	void updatePlaying(float delta);
	void updateGameOver(float delta);
	void updateGameWin(float delta);

	void drawWaiting(sf::RenderWindow &window);
	void drawPlaying(sf::RenderWindow &window);
	void drawGameOver(sf::RenderWindow &window);
	void drawGameWin(sf::RenderWindow &window);

	void reset(void);

	LoadingController _loading;
	ConnectionLostController _connectionLost;
	GameOverController _gameOver;
	HUDController _hud;
	ScoreController _scoreController;
	MessageLayout _messageLayout;

	IClient &_network;
	std::string _partyName;
	std::string _partyPwd;
	Player *_player;
	Mate *_mates[3];
	Background _back;
	Background _front;
	bool _ready;
	bool _reset;
	GameStatusType _state;
};

