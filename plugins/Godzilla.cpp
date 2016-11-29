#include "Godzilla.hpp"

Godzilla::Godzilla() : _Type(ShipType::Boss)
{
}

void Godzilla::update(float delta)
{
	_CanonDegrees = delta;
}

unsigned char Godzilla::getHP(void)
{
	return _HP;
}

unsigned char Godzilla::getFireRate(void)
{
	return _FireRate;
}

unsigned char Godzilla::getSpeed(void)
{
	return _Speed;
}

ShipType Godzilla::getType(void)
{
	return _Type;
}

std::pair<int, int> Godzilla::getNextMove(void)
{
	return std::pair<int, int>();
}

bool Godzilla::fire(void)
{
	return false;
}

std::pair<int, int> Godzilla::getSpawnPosition(void)
{
	return this->_SpawnPosition;
}

std::pair<int, int> Godzilla::getCanonPosition(void)
{
	return this->_CanonPosition;
}

float Godzilla::getCanonDegrees(void)
{
	return _CanonDegrees;
}

void Godzilla::setID(int value)
{
	this->_ID = value;
}
