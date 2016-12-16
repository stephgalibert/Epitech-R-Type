#pragma once

#include "ConnectionManager.hpp"
#include "ScheduledMonster.hpp"
#include "StaticTools.hpp"

class MonsterManager
{
public:
	MonsterManager(ConnectionManager const& cm);
	~MonsterManager(void);

	void init(void);
	void update(float delta);

private:
	ConnectionManager const& _cm;
	ScheduledMonster _sm;
};

