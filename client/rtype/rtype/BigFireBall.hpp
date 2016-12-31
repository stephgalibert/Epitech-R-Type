#pragma once

#include "AProjectile.hpp"

class BigFireBall : public AProjectile
{
public:
	BigFireBall(void);
	virtual ~BigFireBall(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(IClient &client);

	virtual void collision(IClient *client, AEntity *other);
	virtual void applyCollision(CollisionType type, AEntity *other);

private:
	void updateFrame(void);
	void initFrame(void);

private:
	sf::RectangleShape *_shape;
	float _delta;
	uint8_t _currentFrame;
	std::vector<sf::IntRect> _frames;
};

