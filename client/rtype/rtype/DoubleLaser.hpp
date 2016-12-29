#pragma once

#include "AProjectile.hpp"

class DoubleLaser : public AProjectile
{
private:
	static const float COEF_RESIZE;
public:
	DoubleLaser(void);
	virtual ~DoubleLaser(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(IClient &client);

	virtual void collision(IClient *client, AEntity *other);
	virtual void applyCollision(CollisionType type, AEntity *other);

private:
	void initFrame(void);
	void updateFrame(void);

private:
	sf::RectangleShape *_shape;
	float _delta;
	uint8_t _currentFrame;
	std::vector<sf::IntRect> _frames;
};