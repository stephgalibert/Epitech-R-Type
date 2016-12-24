#include "Zorg.hpp"

Zorg::Zorg(void)
{
	std::cout << "creating zorg" << std::endl;
	_id = 0;
	_life = 1;
	_fireRate = 3;
	_velocity = 150;
	_angle = 180;
	_canonsRelativePosition.emplace_back<std::pair<uint16_t, uint16_t> >(std::make_pair(0, 0));
	_canonsDegrees.emplace_back<float>(180);
}

Zorg::~Zorg(void)
{
	std::cout << "deleting zorg" << std::endl;
}

void Zorg::update(double delta)
{
	(void)delta;
}

void Zorg::takeDamage(uint8_t damage)
{
	std::cout << "zorg " << _id << " taking " << damage << " damages" << std::endl;

	if (_life < _life - damage) {
		_life = 0;
	}
	else {
		_life -= damage;
	}
}

void Zorg::setID(uint16_t value)
{
	_id = value;
}

void Zorg::setPosition(uint16_t y)
{
	_position = y;
}

uint16_t Zorg::getID(void) const
{
	return (_id);
}

uint16_t Zorg::getScoreValue(void) const
{
	return (10);
}

uint8_t Zorg::getHP(void) const
{
	return (_life);
}

uint8_t Zorg::getFireRate(void) const
{
	return (_fireRate);
}

uint16_t Zorg::getVelocity(void) const
{
	return (_velocity);
}

uint8_t Zorg::getAngle(void) const
{
	return (_angle);
}

std::string Zorg::getType(void) const
{
	return ("Zork");
}

uint16_t Zorg::getPosition(void) const
{
	return (_position);
}

std::vector<std::pair<uint16_t, uint16_t> > const& Zorg::getCanonRelativePosition(void) const
{
	return (_canonsRelativePosition);
}

std::vector<float> const& Zorg::getCanonDegrees(void) const
{
	return (_canonsDegrees);
}