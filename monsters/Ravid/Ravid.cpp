#include "Ravid.hpp"

Ravid::Ravid(void)
	: _lh("Ravid")
{
	_delta = 0;
	_id = 0;
	_life = 3;
	_fireRate = 2.f;
	_velocity = 50;
	_canonsRelativePosition.emplace_back<std::pair<uint16_t, uint16_t> >(std::make_pair(-40, -20));
	_canonsRelativePosition.emplace_back<std::pair<uint16_t, uint16_t> >(std::make_pair(-40, 0));
	_canonsRelativePosition.emplace_back<std::pair<uint16_t, uint16_t> >(std::make_pair(-40, 20));
	setAngle(180);
	_state = State::None;

	// à l'ia de changer ça :
	_canonsDegrees.emplace_back<float>(180);
	_canonsDegrees.emplace_back<float>(180);
	_canonsDegrees.emplace_back<float>(180);

	_canonsVelocity.emplace_back(230);
	_canonsVelocity.emplace_back(230);
	_canonsVelocity.emplace_back(230);

	_targets.push_back(std::make_pair(-1, -1));
	_targets.push_back(std::make_pair(-1, -1));
	_targets.push_back(std::make_pair(-1, -1));
}

Ravid::~Ravid(void)
{
}

void Ravid::update(double delta, std::vector<PlayerData> const& players)
{
  (void)players;


	clearTargets();
	_lh.getMultiTarget(getPosition(), players, _targets, 3);
	for (uint8_t i = 0; i < 3; i++) {
		_canonsDegrees[i] = static_cast<float>((std::atan2(getPosition().second - _targets[i].second, getPosition().first - _targets[i].first)) * 180.f / 3.14159265359f) - 180.f;
	}
	_delta += delta;


	move(std::cos(_radians) * _velocity * delta, 0);
	//std::cout << "#" << getID() << " x: " << _position.first << std::endl;

	if (_delta > getFireRate() && CanShoot()) {
		_state = State::Fire;
		_delta = 0;
	}
}

void Ravid::takeDamage(uint8_t damage)
{
	if (_life < _life - damage) {
		_life = 0;
	}
	else {
		_life -= damage;
	}

	//std::cout << "Ravid " << _id << " taking " << damage << " damages. Life remaining: " << _life << std::endl;
}

void Ravid::setID(uint16_t value)
{
	_id = value;
}

void Ravid::setPosition(std::pair<double, double> const& pos)
{
	_position = pos;
}

void Ravid::setAngle(double angle)
{
	_angle = angle;
	_radians = _angle * (2.f * 3.14159265f) / 360.f;
}

void Ravid::move(double x, double y)
{
	_position.first += x;
	_position.second += y;
}

IMonster::State Ravid::popAction(void)
{
	State tmp = _state;
	_state = State::None;
	return (tmp);
}

uint16_t Ravid::getID(void) const
{
	return (_id);
}

int Ravid::getDirection(void) const
{
	return (0);
}

uint16_t Ravid::getScoreValue(void) const
{
	return (50);
}

uint8_t Ravid::getHP(void) const
{
	return (_life);
}

double Ravid::getFireRate(void) const
{
	return (_fireRate);
}

uint16_t Ravid::getVelocity(void) const
{
	return (_velocity);
}

uint8_t Ravid::getAngle(void) const
{
	return (static_cast<uint8_t>(_angle));
}

std::string Ravid::getType(void) const
{
	return ("Ravid");
}

std::pair<double, double> const& Ravid::getPosition(void) const
{
	return (_position);
}

std::vector<std::pair<uint16_t, uint16_t> > const& Ravid::getCanonRelativePosition(void) const
{
	return (_canonsRelativePosition);
}

std::vector<float> const& Ravid::getCanonDegrees(void) const
{
	return (_canonsDegrees);
}

std::vector<uint8_t> const& Ravid::getCanonVelocity(void) const
{
	return (_canonsVelocity);
}

void Ravid::clearTargets(void)
{
	for (uint8_t i = 0; i < 3; i++) {
		_targets[i].first = -1;
		_targets[i].second = -1;
	}
}

bool Ravid::CanShoot(void) {
	uint16_t c = 0;

	for (uint8_t i = 0; i < 3; i++) {
		if (_canonsDegrees[i] < -270 || _canonsDegrees[i] > -90)
			c++;
	}
	return (c != 3);
}