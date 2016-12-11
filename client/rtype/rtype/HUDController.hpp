#pragma once

#include "AController.hpp"

#include "Health.hpp"
#include "LoadedShotLayout.hpp"

class HUDController : public AController
{
public:
	HUDController(void);
	virtual ~HUDController(void);

	virtual void init(void);
	virtual bool input(InputHandler &input);
	virtual void update(float delta);
	virtual void draw(sf::RenderWindow &window);
	virtual void recycle(void);

	void setHealth(uint8_t life);
	void setColor(uint16_t color);
	void setLoaded(float deltaLoadedShot);

private:
	float _delta;
	Health _health;
	LoadedShotLayout _shot;
	sf::RectangleShape _shape;
	sf::CircleShape _colorShape;
	//sf::ConvexShape _loadedShotShape;
	std::pair<short, short> _resolution;
};

