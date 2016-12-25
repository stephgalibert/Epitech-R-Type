#include "MonsterManager.hpp"
#include "DLManager.hpp"
#include "CMDSpawnMonster.hpp"
#include "CMDDestroyed.hpp"
#include "AConnection.hpp"

MonsterManager::MonsterManager(ConnectionManager &cm, LevelManager &lm)
	: _cm(cm), _lm(lm)
{
	_dlManager = NULL;
	_delta = 0;
	_nextID = 30000;
}

MonsterManager::~MonsterManager(void)
{
	for (auto it : _monsters) {
		delete (it);
	}

	if (_dlManager) {
		delete (_dlManager);
	}
}

void MonsterManager::init(void)
{
	try {
		_dlManager = new DLManager<IMonster>();
		_dlManager->parseDirectory("monsters/");

		std::vector<MonsterInformation> const& info = _lm.getMonsterInformation();
		for (auto &it : info) {
			_monstersInfo.push(it);
		}
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
	}
}

void MonsterManager::update(double delta)
{
	_delta += delta;

	if (!_monstersInfo.empty()) {
		try {
			MonsterInformation const& info = _monstersInfo.front();
			if (_delta >= info.time) {
				spawnMonster(info);
				_monstersInfo.pop();
			}
		}
		catch (std::exception const& e) {
			StaticTools::Log << e.what() << std::endl;
			_monstersInfo.pop();
		}
	}

	for (auto &it : _monsters) {
		it->update(delta);
		// ...
	}
}

void MonsterManager::addPlayerScore(std::shared_ptr<AConnection> player, uint16_t monsterID)
{
	std::lock_guard<std::mutex> lock(_mutex);

	std::list<IMonster *>::iterator it = _monsters.begin();
	while (it != _monsters.cend()) {
		if ((*it)->getID() == monsterID) {
			player->setScore(player->getScore() + (*it)->getScoreValue());
			return;
		}
		++it;
	}
}

bool MonsterManager::destroyed(uint16_t id)
{
	std::lock_guard<std::mutex> lock(_mutex);
	std::list<IMonster *>::iterator it = _monsters.begin();

	while (it != _monsters.cend()) {
		if ((*it)->getID() == id) {

			delete (*it);
			it = _monsters.erase(it);

			_cm.broadcast(std::make_shared<CMDDestroyed>(id));
			return (true);
		}
		else {
			++it;
		}
	}
	return (false);
}

void MonsterManager::spawnMonster(MonsterInformation const& info)
{
	IMonster *monster = _dlManager->retrieveObject(info.type);

	uint16_t id = _nextID++;
	uint16_t y = info.y;
	uint8_t health = monster->getHP();
	uint16_t velocity = monster->getVelocity();
	uint8_t angle = monster->getAngle();
	std::string type = monster->getType();

	monster->setPosition(y);
	monster->setID(id);

	std::cout << _delta << ": " << "spawning " << type << std::endl;

	_cm.broadcast(std::make_shared<CMDSpawnMonster>(id, 0, y, health, velocity, angle, type));
	_monsters.push_back(monster);
}