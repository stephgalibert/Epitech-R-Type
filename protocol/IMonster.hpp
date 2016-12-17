#pragma once

#include <utility>
#include <stdint.h>
#include <vector>

#include "Protocol.hpp"


class IMonster
{
public:
	virtual void update(float delta) = 0;
	virtual void takeDamage(uint8_t damage) = 0;

	virtual void setID(int value) = 0;

	virtual uint16_t getScoreValue(void) const = 0;
	virtual uint8_t getHP(void) const = 0;
	virtual uint8_t getFireRate(void) const = 0;
	virtual uint16_t getSpeed(void) const = 0;
	virtual ShipType getType(void) const = 0;
	virtual uint16_t getSpawnPosition(void) const = 0;
	virtual std::vector<std::pair<uint16_t, uint16_t> > const& getCanonRelativePosition(void) const = 0;
	virtual std::vector<float> const& getCanonDegrees(void) const = 0;
};