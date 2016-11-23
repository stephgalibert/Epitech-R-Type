#include "PartyManager.h"

PartyManager::PartyManager() {}

PartyManager::~PartyManager() {}

void PartyManager::add(std::string name, std::string pwd) {}

void PartyManager::del(std::string name) {}

std::shared_ptr<Party> PartyManager::addUser(std::string name, std::string pwd, std::shared_ptr<AConnection> user) {
	return std::shared_ptr<Party>();
}