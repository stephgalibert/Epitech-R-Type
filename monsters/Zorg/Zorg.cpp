#include "Zorg.hpp"

Zorg::Zorg(void)
	: _lh("Zorg")
{
	_delta = 0;
	_id = 0;
	_life = 1;
	_fireRate = 3;
	_velocity = 150;
	setAngle(90);
	_canonsRelativePosition.emplace_back<std::pair<uint16_t, uint16_t> >(std::make_pair(-20, 0));
	_canonsDegrees.emplace_back<float>(180);
	_state = State::None;
	_angleState = AngleState::Increase;
	_canonsVelocity.emplace_back(230);
}

Zorg::~Zorg(void)
{
}

void Zorg::update(double delta, std::vector<PlayerData> const& players)
{
	(void)delta;

	std::pair<uint16_t, uint16_t> target = _lh.getTarget(getPosition(), players);
	_canonsDegrees[0] = static_cast<float>((std::atan2(getPosition().second - target.second, getPosition().first - target.first)) * 180.f / 3.14159265359f) - 180.f;
	_delta += delta;
	if (_angleState == AngleState::Increase) {
		if (getAngle() < 230) {
			setAngle(_angle + (delta * 70.f));
		}
		else {
			_angleState = AngleState::Decrease;
		}
	}
	else {
		if (getAngle() > 130) {
			setAngle(_angle - (delta * 70.f));
		}
		else {
			_angleState = AngleState::Increase;
		}
	}

	move(std::cos(_radians) * _velocity * delta, std::sin(_radians) * getVelocity() * delta);
	//std::cout << "#" << getID() << " x: " << _position.first << std::endl;

	if (_delta > getFireRate()) {
		_state = State::Fire;
		_delta = 0;
	}
}

void Zorg::takeDamage(uint8_t damage)
{
	//std::cout << "zorg " << _id << " taking " << damage << " damages" << std::endl;

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

void Zorg::setAngle(double angle)
{
	_angle = angle;
	_radians = _angle * (2.f * 3.14159265f) / 360.f;
}

void Zorg::move(double x, double y)
{
	_position.first += x;
	_position.second += y;
}

IMonster::State Zorg::popAction(void)
{
	State tmp = _state;
	_state = State::None;
	return (tmp);
}

uint16_t Zorg::getID(void) const
{
	return (_id);
}

int Zorg::getDirection(void) const
{
	return (0);
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
	return (static_cast<uint8_t>(_angle));
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

std::vector<uint8_t> const& Zorg::getCanonVelocity(void) const
{
	return (_canonsVelocity);
}