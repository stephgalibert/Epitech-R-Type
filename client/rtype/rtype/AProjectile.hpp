#pragma once

#include "AMoveable.hpp"

class AProjectile : public AMoveable
{
public:
	AProjectile(void);
	virtual ~AProjectile(void);

	virtual void init(void) = 0;
	virtual void update(float delta);
	virtual void destroy(void) = 0;

	virtual void collision(IClient *client, AEntity *other) = 0;

	void setOwnerID(uint8_t ownerID);
	uint8_t getOwnerID(void) const;

	void setLevel(uint8_t level);
	uint8_t getLevel(void) const;

private:
	uint8_t _ownerID;
	uint8_t _currentLevel;
};

