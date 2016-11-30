#include "PartyManager.hpp"

PartyManager::PartyManager(void)
{
}

PartyManager::~PartyManager(void)
{
}

void PartyManager::update(void)
{
	//if (!_toRun.empty()) {
	//	_mutex.lock();

	//	std::shared_ptr<Party> party = _toRun.front();
	//	_toRun.pop();
	//	party->run();
	//	_parties.push_front(party);

	//	_mutex.unlock();
	//}
}

void PartyManager::addParty(std::string const& name, std::string const& pwd)
{
	std::shared_ptr<Party> party = std::make_shared<Party>();

	StaticTools::Log << "Creating party '" + name + ":" + pwd + "'" << std::endl;
	try {

		if (exist(name)) {
			throw (std::runtime_error("The party " + name + " already exist"));
		}
		party->init(name, pwd);
		party->run();
	}
	catch (std::exception const& e) {
		throw (std::runtime_error(e.what()));
	}
	_parties.push_front(party);
	//_mutex.lock();
	//_toRun.push(party);
	//_mutex.unlock();
}

void PartyManager::removeParty(std::string const& name, std::string const& pwd)
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

std::shared_ptr<Party> PartyManager::addConnexion(std::shared_ptr<AConnection> connection, std::string const& name, std::string const& pwd)
{
	std::list<std::shared_ptr<Party> >::iterator it = std::begin(_parties);

	while (it != std::end(_parties) && (*it)->getName() != name && (*it)->getPassword() != pwd) {
		std::cout << name << " " << (*it)->getName() << " ; " << pwd << " " << (*it)->getPassword() << std::endl;
		++it;
	}
	if (it != std::end(_parties)) {
		StaticTools::Log << "Adding connection in party '" + name + ":" + pwd + "'" << std::endl;
		(*it)->addConnection(connection);
		return (*it);
	}
	return (NULL);
}

bool PartyManager::exist(std::string const& name) const
{
	for (auto it : _parties) {
		if (it->getName() == name) {
			return (true);
		}
	}
	return (false);
}