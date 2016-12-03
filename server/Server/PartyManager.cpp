#include "PartyManager.hpp"

PartyManager::PartyManager(void)
{
}

PartyManager::~PartyManager(void)
{
}

void PartyManager::update(void)
{
	if (!_toRun.empty()) {
		_mutex.lock();

		std::pair<std::string, std::shared_ptr<Party> > party = *_toRun.begin();
		_toRun.erase(party.first);
		_parties.insert(party);
		party.second->run();

		_mutex.unlock();
	}
}

void PartyManager::addParty(std::string const& name, std::string const& pwd)
{
	std::shared_ptr<Party> party = std::make_shared<Party>();

	StaticTools::Log << "Creating party '" + name + ":" + pwd + "'" << std::endl;
	try {
		checkPartyExist(name);
		party->init(name, pwd);
	}
	catch (std::exception const& e) {
		throw (std::runtime_error(e.what()));
	}

	_mutex.lock();
	_toRun.insert(std::make_pair(party->getName(), party));
	_mutex.unlock();
}

void PartyManager::removeParty(std::string const& name, std::string const& pwd)
{
	auto &party = _parties.find(name);
	auto &toRun = _toRun.find(name);

	if (party != _parties.cend() && (*party).second->getPassword() == pwd) {
		(*party).second->close();
		_parties.erase(party);
	}
	else if (toRun != _toRun.cend() && (*toRun).second->getPassword() == pwd) {
		(*toRun).second->close();
		_toRun.erase(toRun);
	}
}

std::shared_ptr<Party> PartyManager::addConnexion(std::shared_ptr<AConnection> connection,
													std::string const& name, std::string const& pwd)
{
	_mutex.lock();
	auto &party = _parties.find(name);
	if (party != _parties.cend() && (*party).second->getPassword() == pwd) {
		(*party).second->addConnection(connection);
		_mutex.unlock();
		return ((*party).second);
	}

	auto &toRun = _toRun.find(name);
	if (toRun != _toRun.cend() && (*toRun).second->getPassword() == pwd) {
		(*toRun).second->addConnection(connection);
		_mutex.unlock();
		return ((*toRun).second);
	}
	_mutex.unlock();

	return (NULL);
}

void PartyManager::checkPartyExist(std::string const& name) const
{
	if (_parties.find(name) != _parties.cend() || _parties.find(name) != _parties.cend()) {
		throw (std::runtime_error("The party " + name + " already exist"));
	}
}