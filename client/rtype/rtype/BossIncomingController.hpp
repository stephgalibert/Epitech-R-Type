#pragma once

#include "AController.hpp"

class BossIncomingController : public AController
{
public:
	static const int DELAY_FINISHED = 3;

public:
	BossIncomingController(void);
	virtual ~BossIncomingController(void);

	virtual void init(void);
	virtual bool input(InputHandler &input);
	virtual void update(float delta);
	virtual void draw(sf::RenderWindow &window);
	virtual void recycle(void);

	bool hasFinished(void) const;

private:
	float _delta;
	sf::Text _text;
	std::string _string;
	sf::Color _color;
	std::pair<short, short> _resolution;
	bool _finished;
	bool _started;
};

