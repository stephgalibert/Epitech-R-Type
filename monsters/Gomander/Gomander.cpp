#include "Gomander.hpp"

Gomander::Gomander(void)
{
	_delta = 0;
	_id = 0;
	_life = 5;
	_fireRate = 1.f;
	_velocity = 250;
	_canonsRelativePosition.emplace_back<std::pair<uint16_t, uint16_t> >(std::make_pair(-75, -55));
	_canonsRelativePosition.emplace_back<std::pair<uint16_t, uint16_t> >(std::make_pair(-120, -105));
	_canonsRelativePosition.emplace_back<std::pair<uint16_t, uint16_t> >(std::make_pair(-220, 50));
	_canonsRelativePosition.emplace_back<std::pair<uint16_t, uint16_t> >(std::make_pair(75, 45));
	_canonsRelativePosition.emplace_back<std::pair<uint16_t, uint16_t> >(std::make_pair(210, 50));
	_canonsRelativePosition.emplace_back<std::pair<uint16_t, uint16_t> >(std::make_pair(120, -120));

	setAngle(180);
	_state = State::None;

	_canonsDegrees.emplace_back<float>(225);
	_canonsDegrees.emplace_back<float>(240);
	_canonsDegrees.emplace_back<float>(225);
	_canonsDegrees.emplace_back<float>(-80);
	_canonsDegrees.emplace_back<float>(-70);
	_canonsDegrees.emplace_back<float>(-70);
	_direction = WEAST;

	_canonsVelocity.emplace_back(230);
	_canonsVelocity.emplace_back(230);
	_canonsVelocity.emplace_back(230);
	_canonsVelocity.emplace_back(230);
	_canonsVelocity.emplace_back(230);
	_canonsVelocity.emplace_back(230);
}

Gomander::~Gomander(void)
{
}

void Gomander::update(double delta, std::vector<PlayerData> const& players)
{
  (void)players;

	_delta += delta;

	if (_life > 0) {
		move(std::cos(_radians) * _velocity * delta, 0);

		if (_direction != EAST && _position.first < 200) {
			_state = State::Move;
			_direction = EAST;
			setAngle(0);
		}
		else if (_direction != WEAST && _position.first > StaticTools::GetResolution().first - 200) {
			_state = State::Move;
			_direction = WEAST;
			setAngle(180);
		}

		else if (_delta > getFireRate()) {
			_state = State::Fire;
			_delta = 0;
		}
	}
}

void Gomander::takeDamage(uint8_t damage)
{
	if (_life < _life - damage) {
		_life = 0;
	}
	else {
		_life -= damage;
	}
}

void Gomander::setID(uint16_t value)
{
	_id = value;
}

void Gomander::setPosition(std::pair<double, double> const& pos)
{
	_position = pos;
}

void Gomander::setAngle(double angle)
{
	_angle = angle;
	_radians = _angle * (2.f * 3.14159265f) / 360.f;
}

void Gomander::move(double x, double y)
{
	_position.first += x;
	_position.second += y;
}

IMonster::State Gomander::popAction(void)
{
	State tmp = _state;
	_state = State::None;
	return (tmp);
}

uint16_t Gomander::getID(void) const
{
	return (_id);
}

int Gomander::getDirection(void) const
{
	return(_direction);
}

uint16_t Gomander::getScoreValue(void) const
{
	return (100);
}

uint8_t Gomander::getHP(void) const
{
	return (_life);
}

double Gomander::getFireRate(void) const
{
	return (_fireRate);
}

uint16_t Gomander::getVelocity(void) const
{
	return (_velocity);
}

uint8_t Gomander::getAngle(void) const
{
	return (static_cast<uint8_t>(_angle));
}

std::string Gomander::getType(void) const
{
	return ("Gomander");
}

std::pair<double, double> const& Gomander::getPosition(void) const
{
	return (_position);
}

std::vector<std::pair<uint16_t, uint16_t> > const& Gomander::getCanonRelativePosition(void) const
{
	return (_canonsRelativePosition);
}

std::vector<float> const& Gomander::getCanonDegrees(void) const
{
	return (_canonsDegrees);
}

std::vector<uint8_t> const& Gomander::getCanonVelocity(void) const
{
	return (_canonsVelocity);
}