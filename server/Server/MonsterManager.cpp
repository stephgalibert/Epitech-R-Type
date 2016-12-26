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
		if (it->wantToFire()) {
			shoot(it);
		}
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

	if (_fires.find(id) != _fires.cend()) {
		_fires.erase(id);
		return (true);
	}

	return (false);
}

bool MonsterManager::noMoreIncoming(void) const
{
	return (_monsters.empty() && _monstersInfo.empty());
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

	monster->setPosition(std::make_pair(StaticTools::GetResolution().first, y));
	monster->setID(id);

	_cm.broadcast(std::make_shared<CMDSpawnMonster>(id, 0, y, health, velocity, angle, type));
	_monsters.push_back(monster);
}

void MonsterManager::shoot(IMonster *monster)
{
	std::vector<std::pair<uint16_t, uint16_t> > const& canons = monster->getCanonRelativePosition();
	std::vector<float> const& canonDegrees = monster->getCanonDegrees();

	for (size_t i = 0; i < canons.size(); ++i) {
		MissileType type = MissileType::MT_FriendFire_Lv1;
		uint16_t id = _nextID++;
		uint16_t id_owner = monster->getID();
		uint16_t x = static_cast<uint16_t>(monster->getPosition().first) + canons[i].first;
		uint16_t y = static_cast<uint16_t>(monster->getPosition().second) + canons[i].second;
		uint8_t velocity = 230; // canon dependant
		uint8_t angle = static_cast<uint8_t>(canonDegrees[i]);
		uint8_t effect = 0;
		uint8_t level = 0;

		std::shared_ptr<CMDFire> fire = std::make_shared<CMDFire>(type, id, id_owner, x, y,
			velocity, angle, effect, level);

		_fires.insert(std::make_pair(id, fire));
		_cm.broadcast(fire);
	}
}
