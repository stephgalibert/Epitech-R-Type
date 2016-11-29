#pragma once

#include "IMonster.hpp"

class Godzilla : public IMonster
{
public:
	Godzilla();
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
private:
	ShipType _Type;
	std::pair<int, int> _SpawnPosition;
	std::pair<int, int> _CanonPosition;
	unsigned char _HP;
	unsigned char _FireRate;
	unsigned char _Speed;
	float _CanonDegrees;
	int _ID;
};