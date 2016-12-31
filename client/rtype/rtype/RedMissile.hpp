#pragma once

#include "AProjectile.hpp"
#include "Explosion.hpp"

class RedMissile : public AProjectile
{
private:
	static const float COEF_RESIZE;

public:
	RedMissile(void);
	virtual ~RedMissile(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(IClient &client);

	virtual void collision(IClient *client, AEntity *other);
	virtual void applyCollision(CollisionType type, AEntity *other);

private:
	void initFrame(void);
	void updateFrame(void);

	void collisionDestruction(void);

private:
	sf::RectangleShape *_shape;
	float _delta;
	float _deltaFall;
	uint8_t _currentFrame;
	std::vector<sf::IntRect> _frames;
};

