#include "PartyManager.hpp"

PartyManager::PartyManager(void)
{
}

PartyManager::~PartyManager(void)
{
}

void PartyManager::update(void)
{
	if (!_toRun.empty() || !_parties.empty()) {
		std::lock_guard<std::mutex> lock(_mutex);

		if (!_toRun.empty()) {
			std::pair<std::string, std::shared_ptr<Party> > party = *_toRun.begin();
			_toRun.erase(party.first);
			_parties.insert(party);
			party.second->run();
			std::cout << "insert in parties" << std::endl;
		}

		if (!_parties.empty()) {
			std::unordered_map<std::string, std::shared_ptr<Party> >::iterator it = _parties.begin();
			while (it != _parties.cend()) {
				if ((*it).second->isFinished()) {
					(*it).second->close();
					it = _parties.erase(it);
				}
				else {
					++it;
				}
			}
		}
	}
	StaticTools::sleep(10);
}

void PartyManager::addParty(std::string const& name, std::string const& pwd)
{
	std::lock_guard<std::mutex> lock(_mutex);
	std::shared_ptr<Party> party = std::make_shared<Party>();

	StaticTools::Log << "Creating party '" + name + ":" + pwd + "'" << std::endl;
	try {
		checkPartyExist(name);
		party->init(name, pwd);
	}
	catch (std::exception const& e) {
		//throw (std::runtime_error(e.what()));
		std::cerr << e.what() << std::endl;
		return;
	}

	_toRun.insert(std::make_pair(party->getName(), party));
}

void PartyManager::removeParty(std::string const& name, std::string const& pwd)
{
	std::lock_guard<std::mutex> lock(_mutex);

	auto party = _parties.find(name);
	auto toRun = _toRun.find(name);

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
	std::lock_guard<std::mutex> lock(_mutex);

	auto party = _parties.find(name);
	if (party != _parties.cend() && (*party).second->getPassword() == pwd) {
		(*party).second->addConnection(connection);
		std::cout << "found in parties" << std::endl;
		return ((*party).second);
	}
	else {
		std::cout << "not found in parties: " << name << ":" << pwd << std::endl;
	}

	auto toRun = _toRun.find(name);
	if (toRun != _toRun.cend() && (*toRun).second->getPassword() == pwd) {
		(*toRun).second->addConnection(connection);
		std::cout << "found in toRun" << std::endl;
		return ((*toRun).second);
	}
	else {
		std::cout << "not found in toRun" << std::endl;
	}

	return (NULL);
}

std::unordered_map<std::string, std::shared_ptr<Party> > const& PartyManager::getParties(void) const
{
	return (_parties);
}

void PartyManager::checkPartyExist(std::string const& name) const
{
	if (_parties.find(name) != _parties.cend() || _parties.find(name) != _parties.cend()) {
		throw (std::runtime_error("The party " + name + " already exist"));
	}
}
