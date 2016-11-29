#include "AConnection.hpp"

AConnection::AConnection(ConnectionManager &cm, RequestHandler &rh, PartyManager &pm)
	: _cm(cm),
	  _rh(rh),
	  _pm(pm),
	  _running(false),
	  _id(0),
	  _ready(false)
{
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

void AConnection::setID(int id)
{
	_id = id;
}

void AConnection::setRunning(bool value)
{
	_running = value;
}

void AConnection::setReady(bool value)
{
	_ready = value;
}

std::shared_ptr<Party> AConnection::getCurrentParty(void) const
{
	return (_party);
}

int AConnection::getID(void) const
{
	return (_id);
}

bool AConnection::isRunning(void) const
{
	return (_running);
}

bool AConnection::isReady(void) const
{
	return (_ready);
}