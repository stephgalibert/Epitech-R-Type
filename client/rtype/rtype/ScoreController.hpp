#pragma once

#include <sstream>

#include "AController.hpp"
#include "Player.hpp"
#include "Mate.hpp"

class ScoreController : public AController
{
public:
	ScoreController(Player **player, Mate **mates);
	virtual ~ScoreController(void);

	virtual void init(void);
	virtual bool input(InputHandler &input);
	virtual void update(float delta);
	virtual void draw(sf::RenderWindow &window);
	virtual void recycle(void);

	void setVisible(bool value);
	void setMarginTop(int value);
	void setColor(sf::Color const& color);

private:
	double _delta;
	bool _visible;
	sf::Text _text[4];
	std::string _string[4];
	std::pair<short, short> _resolution;
	Player **_player;
	Mate **_mates;
	int _marginTop;
	sf::Color _color;
};

