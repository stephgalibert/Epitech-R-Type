#pragma once

#include <list>

#include "Party.hpp"

class PartyManager
{
public:
	PartyManager(void);
	~PartyManager(void);

	void add(std::string name, std::string pwd);
	void del(std::string name);
	std::shared_ptr<Party> addUser(std::string name, std::string pwd, std::shared_ptr<AConnection> user);

private:
	std::list<std::shared_ptr<Party> > _parties;
};

