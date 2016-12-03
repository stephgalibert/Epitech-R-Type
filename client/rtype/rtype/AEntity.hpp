#pragma once

#include "ADrawable.hpp"

#define EAST 1
#define WEAST 2
#define NORTH 4
#define SOUTH 8

class AEntity : public ADrawable
{
public:
	AEntity(void);
	virtual ~AEntity(void);

	virtual void init(void) = 0;
	virtual void update(float delta) = 0;
	virtual void destroy(void) = 0;

	void recycle(void);
	bool isWaitingForRecycle(void) const;
	bool isInitialized(void) const;

	void setDirection(uint8_t direction);
	uint8_t getDirection(void) const;

	void move(float delta);

	void setVelocity(float velocity);
	float getVelocity(void) const;

	void setAngle(float angle);
	float getAngle(void) const;

	void setID(uint8_t id);
	uint8_t getID(void) const;

protected:
	bool _init;

private:
	bool _waitingForRecycle;
	uint8_t _id;
	float _velocity;
	float _degrees;
	float _radians;
	uint8_t _direction;
};