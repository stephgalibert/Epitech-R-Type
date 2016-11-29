#include "Party.hpp"

Party::Party(void)
{
}

Party::~Party(void)
{
}

void Party::init(std::string name, std::string pwd)
{
  (void)name;
  (void)pwd;
}

void Party::run(void)
{

}

void Party::close(void)
{

}

void Party::addConnection(std::shared_ptr<AConnection> connection)
{
  (void)connection;
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
}

std::string const& Party::getName(void) const
{
	return (_name);
}

std::string const& Party::getPassword(void) const
{
	return (_password);
}
