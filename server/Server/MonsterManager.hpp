#pragma once
#include "ConnectionManager.hpp"
#include "ScheduledMonster.hpp"

class MonsterManager
{
public:
	MonsterManager(ConnectionManager const& cm);
	~MonsterManager();

	void update();

private:
	ConnectionManager const& _cm;
	ScheduledMonster _sm;
};

