#pragma once

#include "AEntity.hpp"

class AActor : public AEntity
{
public:
	AActor(void);
	virtual ~AActor(void);

	void setID(uint8_t id);
	uint8_t getID(void) const;

private:
	uint8_t _id;
};

