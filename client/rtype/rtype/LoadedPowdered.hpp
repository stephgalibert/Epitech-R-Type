#pragma once

#include "AEntity.hpp"
#include "LevelResource.hpp"

class LoadedPowdered : public AEntity
{
public:
	LoadedPowdered(void);
	virtual ~LoadedPowdered(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(void);

	virtual void collision(IClient *client, AEntity *other);
	virtual void applyCollision(CollisionType type);
	virtual void move(float delta);

	void setColor(uint8_t color);

private:
	void initFrame(void);
	void updateFrame(void);

	sf::RectangleShape *_shape;
	float _delta;
	uint8_t _currentFrame;
	uint8_t _color;
	std::vector<sf::IntRect> _frames;
};

