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

	void addParty(std::string name, std::string pwd);
	void removeParty(std::string name, std::string pwd);
	std::shared_ptr<Party> addConnexion(std::shared_ptr<AConnection> user, std::string name, std::string pwd);

private:
	bool exist(std::string const& name) const;

	std::list<std::shared_ptr<Party> > _parties;

	std::mutex _mutex;
	std::queue<std::shared_ptr<Party> > _toRun;
};

