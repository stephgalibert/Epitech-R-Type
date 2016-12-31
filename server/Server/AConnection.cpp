#include "AConnection.hpp"

AConnection::AConnection(ConnectionManager &cm, RequestHandler &rh, PartyManager &pm)
	: _cm(cm),
	  _rh(rh),
	  _pm(pm),
	  _running(false),
	  _ready(false),
	  //_id(0),
	  _life(3),
	  _score(0)
{
	_playerData.id = 0;
	_playerData.x = 0;
	_playerData.y = 0;
}

AConnection::~AConnection(void)
{
}

void AConnection::update(double delta)
{
	if (_angle != -1) {
		double x = std::cos(_radians) * _velocity * delta;
		double y = std::sin(_radians) * _velocity * delta;

		if (_playerData.x + x < 0 || _playerData.x + x > StaticTools::GetResolution().first) {
			x = 0;
		}
		if (_playerData.y + y < 0 || _playerData.y + y > StaticTools::GetResolution().second) {
			y = 0;
		}
		setPosition(_playerData.x + x, _playerData.y + y);
	}
}

ConnectionManager &AConnection::getConnectionManager(void)
{
	return (_cm);
}

PartyManager &AConnection::getPartyManager(void)
{
	return _pm;
}

RequestHandler &AConnection::getRequestHandler(void)
{
	return _rh;
}

void AConnection::setCurrentParty(std::shared_ptr<Party> party)
{
	_party = party;
}

void AConnection::setID(uint16_t id)
{
	//_id = id;
	_playerData.id = id;
}

void AConnection::setName(std::string const& name)
{
	_name = name;
}

void AConnection::setLife(uint8_t life)
{
	_life = life;
}

void AConnection::setScore(uint16_t score)
{
	_score = score;
}

void AConnection::setRunning(bool value)
{
	_running = value;
}

void AConnection::setReady(bool value)
{
	_ready = value;
}

void AConnection::setPosition(double x, double y)
{
	_playerData.x = x;
	_playerData.y = y;
}

void AConnection::setDirection(int direction)
{
	setAngle(-1);
	if (direction & NORTH) {
		setAngle(-90.f);
	}
	else if (direction & SOUTH) {
		setAngle(90.f);
	}

	if (direction & EAST) {
		setAngle(std::ceil(getAngle() / 2.f));
	}
	else if (direction & WEAST) {
		setAngle(std::floor(-180.f - getAngle() / 2.f));
	}

	_direction = direction;
}

void AConnection::setVelocity(float velocity)
{
	_velocity = velocity;
}

void AConnection::setAngle(float angle)
{
	_angle = angle;
	_radians = _angle * (2.f * 3.14159265f) / 360.f;
}

void AConnection::setEffect(EffectType type, bool toAdd)
{
	if (toAdd) {
		_effects.insert(type);
	}
	else {
		_effects.erase(type);
	}
}

std::shared_ptr<Party> AConnection::getCurrentParty(void) const
{
	return (_party);
}

std::string const& AConnection::getName(void) const
{
	return (_name);
}

uint8_t AConnection::getLife(void) const
{
	return (_life);
}

uint16_t AConnection::getScore(void) const
{
	return (_score);
}

bool AConnection::isRunning(void) const
{
	return (_running);
}

bool AConnection::isReady(void) const
{
	return (_ready);
}

float AConnection::getAngle(void) const
{
	return (_angle);
}

float AConnection::getVelocity(void) const
{
	return (_velocity);
}

PlayerData const& AConnection::getPlayerData(void) const
{
	return (_playerData);
}

bool AConnection::isEffectPresent(EffectType type) const
{
	return (_effects.find(type) != _effects.cend());
}