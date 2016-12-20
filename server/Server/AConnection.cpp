#include "AConnection.hpp"

AConnection::AConnection(ConnectionManager &cm, RequestHandler &rh, PartyManager &pm)
	: _cm(cm),
	  _rh(rh),
	  _pm(pm),
	  _running(false),
	  _ready(false),
	  _id(0),
	  _life(3),
	  _score(0)
{
	_position.first = 20;
	_position.second = 20;
}

AConnection::~AConnection(void)
{
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
	_id = id;
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

void AConnection::setPosition(std::pair<uint16_t, uint16_t> const& position)
{
	_position.first = position.first;
	_position.second = position.second;
}

std::shared_ptr<Party> AConnection::getCurrentParty(void) const
{
	return (_party);
}

uint16_t AConnection::getID(void) const
{
	return (_id);
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

std::pair<uint16_t, uint16_t> const& AConnection::getPosition(void) const
{
	return (_position);
}