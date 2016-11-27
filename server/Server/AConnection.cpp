#include "AConnection.hpp"

AConnection::AConnection(ConnectionManager &cm, RequestHandler &rh, PartyManager &pm)
	: _cm(cm), _rh(rh), _pm(pm), _running(false)
{
}

AConnection::~AConnection(void)
{
}

void AConnection::start(void)
{
	_running = true;
	read();
}

void AConnection::close(void)
{
	_running = false;
}

PartyManager const& AConnection::getPartyManager(void) const
{
	return _pm;
}

RequestHandler const& AConnection::getRequestHandler(void) const
{
	return _rh;
}

std::shared_ptr<Party> AConnection::getCurrentParty(void) const
{
	//return _party;
	return (NULL);
}

void AConnection::setID(int id)
{
	_id = id;
}

void AConnection::read(void)
{

}

void AConnection::do_read(void)
{

}

void AConnection::write(void)
{

}

void AConnection::do_write(void)
{

}