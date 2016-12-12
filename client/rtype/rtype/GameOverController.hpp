#pragma once

#include "AController.hpp"

class GameOverController : public AController
{
public:
	static const int DELAY_RESTARTING = 10;
public:
	GameOverController(void);
	virtual ~GameOverController(void);

	virtual void init(void);
	virtual bool input(InputHandler &input);
	virtual void update(float delta);
	virtual void draw(sf::RenderWindow &window);
	virtual void recycle(void);

private:
	float _delta;
	sf::Text _text;
	sf::Text _restartingIn;
	std::string _string;
	std::string _stringRestartingIn;
	std::pair<short, short> _resolution;
	uint8_t _chronoRestarting;
};

