#include "Monster.hpp"

Monster::Monster() : _Type(ShipType::Standard)
{
}

void Monster::update(float delta)
{
	_CanonDegrees = delta;
}

unsigned char Monster::getHP(void)
{
	return _HP;
}

unsigned char Monster::getFireRate(void)
{
	return _FireRate;
}

unsigned char Monster::getSpeed(void)
{
	return _Speed;
}

ShipType Monster::getType(void)
{
	return _Type;
}

std::pair<int, int> Monster::getNextMove(void)
{
	return std::pair<int, int>();
}

bool Monster::fire(void)
{
	return false;
}

std::pair<int, int> Monster::getSpawnPosition(void)
{
	return this->_SpawnPosition;
}

std::pair<int, int> Monster::getCanonPosition(void)
{
	return this->_CanonPosition;
}

float Monster::getCanonDegrees(void)
{
	return _CanonDegrees;
}

void Monster::setID(int value)
{
	this->_ID = value;
}
