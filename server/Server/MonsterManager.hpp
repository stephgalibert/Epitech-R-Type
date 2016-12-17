#pragma once

#include "ConnectionManager.hpp"
#include "StaticTools.hpp"
#include "ScheduledMonster.hpp"

#include "IMonster.hpp"

template<typename T>
class DLManager;

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
	DLManager<IMonster> *_dlManager;
};

