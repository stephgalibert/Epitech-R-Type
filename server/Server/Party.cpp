#include "Party.hpp"

Party::Party(void)
	: _running(false)
{
}

Party::~Party(void)
{
	_running = false;
	if (_party.joinable()) {
		_party.join();
	}
}

void Party::init(std::string name, std::string pwd)
{
	_name = name;
	_password = pwd;
}

void Party::run(void)
{
	_running = true;
	_party = std::thread(&Party::loop, shared_from_this());
}

void Party::close(void)
{
	_running = false;
	_cm.closeAll();
}

void Party::addConnection(std::shared_ptr<AConnection> connection)
{
	_cm.add(connection);
}

void Party::removeConnection(std::shared_ptr<AConnection> connection)
{
	_cm.leave(connection);
}

void Party::move(char * data)
{
  (void)data;
}

void Party::fire(char * data)
{
  (void)data;
}

void Party::disconnected(char * data)
{
  (void)data;
}

void Party::collision(char * data)
{
  (void)data;
}

void Party::loop(void)
{
	std::cout << "begin loop" << std::endl;
	while (_running) {
		std::cout << "There is " << _cm.getPlayerNumber() << " player(s)." << std::endl;
	}
	std::cout << "end loop" << std::endl;
}

std::string const& Party::getName(void) const
{
	return (_name);
}

std::string const& Party::getPassword(void) const
{
	return (_password);
}
