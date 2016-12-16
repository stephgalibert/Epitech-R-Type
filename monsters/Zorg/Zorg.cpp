#include "Zorg.hpp"

Zorg::Zorg(void)
{
	std::cout << "creating zorg" << std::endl;
}

Zorg::~Zorg(void)
{
	std::cout << "deleting zorg" << std::endl;
}

void Zorg::update(float delta)
{
	(void)delta;
	std::cout << "refresh zorg" << std::endl;
}

unsigned char Zorg::getHP(void)
{
	return (0);
}

unsigned char Zorg::getFireRate(void)
{
	return (0);
}

unsigned char Zorg::getSpeed(void)
{
	return (150);
}

ShipType Zorg::getType(void)
{
	return (ShipType::Standard);
}

std::pair<int, int> Zorg::getNextMove(void)
{
	return (std::make_pair(0, 0));
}

bool Zorg::fire(void)
{
	return (false);
}

std::pair<int, int> Zorg::getSpawnPosition(void)
{
	return (std::make_pair(300, 300));
}

std::pair<int, int> Zorg::getCanonPosition(void)
{
	return (std::make_pair(0, 0));
}

float Zorg::getCanonDegrees(void)
{
	return (45);
}

void Zorg::setID(int value)
{
	(void)value;
}