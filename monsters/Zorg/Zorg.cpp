#include "Zorg.hpp"

Zorg::Zorg(void)
{
	_delta = 0;
	_id = 0;
	_life = 1;
	_fireRate = 3;
	_velocity = 150;
	_angle = 180;
	_radians = _angle * (2.f * 3.14159265f) / 360.f;
	//_canonsRelativePosition.emplace_back<std::pair<uint16_t, uint16_t> >(std::make_pair(-20, -5));
	//_canonsDegrees.emplace_back<float>(180);

	//_canonsRelativePosition.emplace_back<std::pair<uint16_t, uint16_t> >(std::make_pair(-20, 5));
	//_canonsDegrees.emplace_back<float>(180);

	_canonsRelativePosition.emplace_back<std::pair<uint16_t, uint16_t> >(std::make_pair(-20, -5));
	_canonsDegrees.emplace_back<float>(225);

	_canonsRelativePosition.emplace_back<std::pair<uint16_t, uint16_t> >(std::make_pair(-20, 5));
	_canonsDegrees.emplace_back<float>(135);
	_state = State::None;
}

Zorg::~Zorg(void)
{
}

void Zorg::update(double delta)
{
	(void)delta;

	_delta += delta;

	move(std::cos(_radians) * _velocity * delta, 0);
	//std::cout << "#" << getID() << " x: " << _position.first << std::endl;

	if (_delta > getFireRate()) {
		_state = State::Fire;
		_delta = 0;
	}
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

void Zorg::setPosition(std::pair<double, double> const& pos)
{
	_position = pos;
}

void Zorg::move(double x, double y)
{
	_position.first += x;
	_position.second += y;
}

bool Zorg::wantToFire(void)
{
	bool ret = _state == State::Fire;
	_state = State::None;
	return (ret);
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

double Zorg::getFireRate(void) const
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

std::pair<double, double> const& Zorg::getPosition(void) const
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