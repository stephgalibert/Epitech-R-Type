#pragma once

#include <string>
#include <queue>
#include <list>
#include <memory>
#include <unordered_map>

#include "ConnectionManager.hpp"
#include "StaticTools.hpp"

#include "IMonster.hpp"
#include "LevelManager.hpp"
#include "Generator.hpp"

template<typename T>
class DLManager;
class AConnection;

class MonsterManager
{
public:
	MonsterManager(ConnectionManager &cm, LevelManager &lm);
	~MonsterManager(void);

	void init(void);
	void update(double delta);

	void addPlayerScore(std::shared_ptr<AConnection> player, uint16_t monsterID);
	void takeDamage(uint16_t monsterID);
	bool destroyed(uint16_t id);

	bool noMoreIncoming(void) const;

private:
	void spawnMonster(MonsterInformation const& info);
	void shoot(IMonster *monster);
	void move(IMonster *monster);

private:
	ConnectionManager &_cm;
	LevelManager &_lm;
	DLManager<IMonster> *_dlManager;
	double _delta;
	std::queue<MonsterInformation> _monstersInfo;
	std::list<IMonster *> _monsters;
	uint16_t _nextID;
	std::mutex _mutex;

	std::unordered_map<uint16_t, std::shared_ptr<ICommand> > _fires;
	Generator _generator;
};

