#pragma once

#include <vector>

#include "AEntity.hpp"
#include "LevelResource.hpp"

class Powdered : public AEntity
{
public:
	Powdered(void);
	virtual ~Powdered(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(void);

	virtual void collision(IClient *client, AEntity *other);
	virtual void move(float delta);

	void setColor(uint8_t color);
	bool isAnimationFinished(void) const;

private:
	void initFrame(void);
	void updateFrame(void);

	sf::RectangleShape *_shape;
	float _delta;
	uint8_t _currentFrame;
	uint8_t _color;
	std::vector<sf::IntRect> _frames;
	bool _finished;
};

