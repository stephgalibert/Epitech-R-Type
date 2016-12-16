#pragma once

#ifdef WIN32
# define MONSTER_API __declspec(dllexport)
#else
# define MONSTERAPI
#endif

#include <iostream>

#include "IMonster.hpp"

class Zorg : public IMonster
{
public:
	Zorg(void);
	virtual ~Zorg(void);

	virtual void update(float delta);
	virtual unsigned char getHP(void);
	virtual unsigned char getFireRate(void);
	virtual unsigned char getSpeed(void);
	virtual ShipType getType(void);
	virtual std::pair<int, int> getNextMove(void);
	virtual bool fire(void);
	virtual std::pair<int, int> getSpawnPosition(void);
	virtual std::pair<int, int> getCanonPosition(void);
	virtual float getCanonDegrees(void);
	virtual void setID(int value);
};

extern "C" MONSTER_API IMonster *entry(void)
{
	return (new Zorg);
}