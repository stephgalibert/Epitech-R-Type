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

void Party::connect(std::shared_ptr<AConnection> user)
{
  (void)user;
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
