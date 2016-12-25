#pragma once

#include "AController.hpp"

class GameWinController : public AController
{
public:
	static const int DELAY_RESTARTING = 10;

public:
	GameWinController(void);
	virtual ~GameWinController(void);

	virtual void init(void);
	virtual bool input(InputHandler &input);
	virtual void update(float delta);
	virtual void draw(sf::RenderWindow &window);
	virtual void recycle(void);

	bool hasFinished(void) const;

private:
	float _delta;
	sf::Text _text;
	sf::RectangleShape _shape;
	sf::Color _color;
	std::string _string;
	std::pair<short, short> _resolution;
	bool _finished;
	bool _started;
};

