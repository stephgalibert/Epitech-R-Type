#include "Dop.hpp"

Dop::Dop(void)
{
	_delta = 0;
	_id = 0;
	_life = 2;
	_fireRate = 1.5f;
	_velocity = 100;
	_canonsRelativePosition.emplace_back<std::pair<uint16_t, uint16_t> >(std::make_pair(-40, 0));
	setAngle(180);
	_state = State::None;

	_canonsDegrees.emplace_back<float>(180);
	_canonsVelocity.emplace_back(150);

	_delta = _fireRate;
}

Dop::~Dop(void)
{
}

void Dop::update(double delta, std::vector<PlayerData> const& players)
{
  (void)players;

	_delta += delta;

	move(std::cos(_radians) * _velocity * delta, 0);
	//std::cout << "#" << getID() << " x: " << _position.first << std::endl;

	if (_delta > getFireRate()) {
		_state = State::Fire;
		_delta = 0;
	}
}

void Dop::takeDamage(uint8_t damage)
{
	if (_life < _life - damage) {
		_life = 0;
	}
	else {
		_life -= damage;
	}

	//std::cout << "dop " << _id << " taking " << damage << " damages. Life remaining: " << _life << std::endl;
}

void Dop::setID(uint16_t value)
{
	_id = value;
}

void Dop::setPosition(std::pair<double, double> const& pos)
{
	_position = pos;
}

void Dop::setAngle(double angle)
{
	_angle = angle;
	_radians = _angle * (2.f * 3.14159265f) / 360.f;
}

void Dop::move(double x, double y)
{
	_position.first += x;
	_position.second += y;
}

IMonster::State Dop::popAction(void)
{
	State tmp = _state;
	_state = State::None;
	return (tmp);
}

uint16_t Dop::getID(void) const
{
	return (_id);
}

int Dop::getDirection(void) const
{
	return (0);
}

uint16_t Dop::getScoreValue(void) const
{
	return (20);
}

uint8_t Dop::getHP(void) const
{
	return (_life);
}

double Dop::getFireRate(void) const
{
	return (_fireRate);
}

uint16_t Dop::getVelocity(void) const
{
	return (_velocity);
}

uint8_t Dop::getAngle(void) const
{
	return (static_cast<uint8_t>(_angle));
}

std::string Dop::getType(void) const
{
	return ("Dop");
}

std::pair<double, double> const& Dop::getPosition(void) const
{
	return (_position);
}

std::vector<std::pair<uint16_t, uint16_t> > const& Dop::getCanonRelativePosition(void) const
{
	return (_canonsRelativePosition);
}

std::vector<float> const& Dop::getCanonDegrees(void) const
{
	return (_canonsDegrees);
}

std::vector<uint8_t> const& Dop::getCanonVelocity(void) const
{
	return (_canonsVelocity);
}