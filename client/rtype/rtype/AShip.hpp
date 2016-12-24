#pragma once

#include "AMoveable.hpp"

#include "World.hpp"

class AShip : public AMoveable
{
public:
	AShip(void);
	virtual ~AShip(void);

	virtual void init(void) = 0;
	virtual void update(float delta);
	virtual void destroy(IClient &client) = 0;

	virtual void collision(IClient *client, AEntity *other) = 0;
	virtual void applyCollision(CollisionType type, AEntity *other) = 0;
	virtual void move(float delta);

	virtual void shoot(Fire const& param) = 0;
	virtual void respawn(void) = 0;

	void setScore(uint16_t score);
	uint16_t getScore(void) const;

	void setName(std::string const& name);
	std::string const& getName(void) const;

private:
	uint16_t _score;
	std::string _name;
};

