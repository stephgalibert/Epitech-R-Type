#include "PartyManager.hpp"

PartyManager::PartyManager(void)
{
}

PartyManager::~PartyManager(void)
{
}

void PartyManager::add(std::string name, std::string pwd)
{
  (void)name;
  (void)pwd;
}

void PartyManager::del(std::string name)
{
  (void)name;
}

std::shared_ptr<Party> PartyManager::addUser(std::string name, std::string pwd, std::shared_ptr<AConnection> user)
{
  (void)name;
  (void)pwd;
  (void)user;
	return std::shared_ptr<Party>();
}
