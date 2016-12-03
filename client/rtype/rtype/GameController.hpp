#pragma once

#include <iostream>
#include <string>

#include "World.hpp"
#include "AController.hpp"

#include "Background.hpp"
#include "Player.hpp"

#include "IClient.hpp"
#include "CMDConnect.hpp"

class GameController : public AController
{
public:
	GameController(IClient &network, std::string const& partyName, std::string const& partyPwd);
	virtual ~GameController(void);

	virtual void init(void);
	virtual bool input(InputHandler &input);
	virtual void update(float delta);
	virtual void draw(sf::RenderWindow &window);
	virtual void recycle(void);

private:
	IClient &_network;
	std::string _partyName;
	std::string _partyPwd;
	Player *_player;
	Background _back;
	Background _front;
};

