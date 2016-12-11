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

	void connectToParty(std::string const& partyName, std::string const& pwd);

	void setReady(bool value);
	void setPlayer(Player *player);

	Player *getPlayer(void) const;
	//void addMate(Mate *mate);

	bool isReady(void) const;

private:
	LoadingController _loading;
	ConnectionLostController _connectionLost;
	HUDController _hud;

	IClient &_network;
	std::string _partyName;
	std::string _partyPwd;
	Player *_player;
	// mates
	Background _back;
	Background _front;
	bool _ready;
};

