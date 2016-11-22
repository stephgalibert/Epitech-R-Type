#pragma once

#include "AEntity.hpp"

class AActor : public AEntity
{
public:
	AActor(void);
	virtual ~AActor(void);

	virtual void init(void) = 0;
	virtual void update(float delta) = 0;
	virtual void destroy(void) = 0;

	void setID(uint8_t id);
	uint8_t getID(void) const;

private:
	uint8_t _id;
};

