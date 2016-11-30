#pragma once

#include <list>
#include <mutex>

#include "Party.hpp"

class PartyManager
{
public:
	PartyManager(void);
	~PartyManager(void);

	void update(void);

	void addParty(std::string const& name, std::string const& pwd);
	void removeParty(std::string const& name, std::string const& pwd);
	std::shared_ptr<Party> addConnexion(std::shared_ptr<AConnection> user, std::string const& name, std::string const& pwd);

private:
	bool exist(std::string const& name) const;

	std::list<std::shared_ptr<Party> > _parties;

	std::mutex _mutex;
	std::queue<std::shared_ptr<Party> > _toRun;
};

