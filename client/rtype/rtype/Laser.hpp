#pragma once

#include <unordered_map>

#include "AProjectile.hpp"
#include "LevelResource.hpp"
#include "Explosion.hpp"
#include "World.hpp"

class Laser : public AProjectile
{
public:
	Laser(void);
	virtual ~Laser(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(void);

	virtual void collision(IClient *client, ACollidable *other);

	void setColor(uint8_t color);

private:
	void initFrame(void);
	void updateFrame(void);

	sf::RectangleShape *_shape;

	float _delta;
	uint8_t _currentFrame;
	uint8_t _color;
	std::unordered_map<uint8_t, sf::IntRect[2]> _frames;
};

