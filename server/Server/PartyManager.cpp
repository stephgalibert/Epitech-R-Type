#include "PartyManager.hpp"

PartyManager::PartyManager(void)
{
}

PartyManager::~PartyManager(void)
{
}

void PartyManager::addParty(std::string name, std::string pwd)
{
	std::shared_ptr<Party> party = std::make_shared<Party>();

	try {
		StaticTools::Log << "Create party '" + name + ":" + pwd + "'" << std::endl;
		party->init(name, pwd);
	}
	catch (std::exception const& e) {
		throw (std::runtime_error(e.what()));
	}
	_parties.push_front(party);
	party->run();
}

void PartyManager::removeParty(std::string name, std::string pwd)
{
	std::list<std::shared_ptr<Party> >::iterator it = std::begin(_parties);

	while (it != std::end(_parties)) {
		if ((*it)->getName() == name && (*it)->getPassword() == pwd) {
			StaticTools::Log << "Closing party '" + name + ":" + pwd + "'" << std::endl;
			(*it)->close();
			it = _parties.erase(it);
		}
		else {
			++it;
		}
	}
}

std::shared_ptr<Party> PartyManager::addUser(std::string name, std::string pwd, std::shared_ptr<AConnection> connection)
{
	std::list<std::shared_ptr<Party> >::iterator it = std::begin(_parties);

	while (it != std::end(_parties) && (*it)->getName() != name && (*it)->getPassword() != pwd) {
		++it;
	}
	if (it != std::end(_parties)) {
		StaticTools::Log << "Adding connection in party '" + name + ":" + pwd + "'" << std::endl;
		(*it)->addConnection(connection);
		return (*it);
	}
	return (NULL);
}
