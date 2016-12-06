#pragma once

#include "ACollidable.hpp"

#define EAST 1
#define WEAST 2
#define NORTH 4
#define SOUTH 8

class AEntity : public ACollidable
{
public:
	AEntity(void);
	virtual ~AEntity(void);

	virtual void init(void) = 0;
	virtual void update(float delta) = 0;
	virtual void destroy(void) = 0;

	virtual void collision(IClient *client, ACollidable *other) = 0;

	virtual void move(float delta) = 0;

	void setReadyForInit(bool value);
	bool isReadyForInit(void) const;

	void setDirection(uint8_t direction);
	uint8_t getDirection(void) const;

	void setVelocity(float velocity);
	float getVelocity(void) const;

	void setAngle(float angle);
	float getAngle(void) const;
	float getRadians(void) const;

	void setID(uint8_t id);
	uint8_t getID(void) const;

private:
	bool _readyForInit;
	uint8_t _id;
	float _velocity;
	float _degrees;
	float _radians;
	uint8_t _direction;
};