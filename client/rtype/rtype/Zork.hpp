#pragma once

#include "ANPC.hpp"
#include "FireBall.hpp"

class Zork : public ANPC
{
private:
	static const float COEF_RESIZE;

public:
	Zork(void);
	virtual ~Zork(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(IClient &client);

	virtual void collision(IClient *client, AEntity *other);
	virtual void applyCollision(CollisionType type, AEntity *other);
	virtual void move(float delta);

	virtual void shoot(Fire const& param);
	virtual void setPowder(PowderType powderType);

	virtual void respawn(void);

private:
	void initFrame(void);
	void updateFrame(void);

	void collisionDestruction(void);

private:
	float _delta;
	uint8_t _currentFrame;

	sf::RectangleShape *_shape;

	std::vector<sf::IntRect> _frames;
};

