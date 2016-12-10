#pragma once

#include "AShip.hpp"

#include "InputHandler.hpp"

class APC : public AShip
{
public:
	APC();
	virtual ~APC(void);

	virtual void init(void) = 0;
	virtual void update(float delta);
	virtual void destroy(void) = 0;

	virtual void collision(IClient *client, AEntity *other) = 0;
	virtual void applyCollision(CollisionType type) = 0;
	virtual void input(InputHandler &input) = 0;
	virtual void move(float delta);

	virtual void shoot(Fire const& param) = 0;
};