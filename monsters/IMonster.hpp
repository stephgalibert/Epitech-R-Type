#pragma once

#include "Protocol.hpp"
#include <utility>

class IMonster
{
public:
	virtual void update(float delta) = 0;
	virtual unsigned char getHP(void) = 0;
	virtual unsigned char getFireRate(void) = 0;
	virtual unsigned char getSpeed(void) = 0;
	virtual ShipType getType(void) = 0;
	virtual std::pair<int, int> getNextMove(void) = 0;
	virtual bool fire(void) = 0;
	virtual std::pair<int, int> getSpawnPosition(void) = 0;
	virtual std::pair<int, int> getCanonPosition(void) = 0;
	virtual float getCanonDegrees(void) = 0;
	virtual void setID(int value) = 0;
};