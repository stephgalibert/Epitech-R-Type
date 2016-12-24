#include "LevelManager.hpp"

LevelManager::LevelManager(void)
{
	_currentLevel = 0;
}

LevelManager::~LevelManager(void)
{
}

void LevelManager::initialize(void)
{
	try {
		setLevel(1);
	}
	catch (std::exception const& e) {
		throw (std::runtime_error(e.what()));
	}
}

void LevelManager::setLevel(uint8_t level)
{
	_currentLevel = level;
	parseLevel();
}

uint8_t LevelManager::getLevel(void) const
{
	return (_currentLevel);
}

std::vector<MonsterInformation> const& LevelManager::getMonsterInformation(void) const
{
	return (_monsters);
}

void LevelManager::parseLevel(void)
{
	LevelParser parser;

	try {
		parser.parse(_currentLevel);
		std::vector<std::vector<std::string> > const& data = parser.getData();

		for (auto &it : data) {
			if (it[0] == "MONSTER") {
				_monsters.emplace_back(it[1], std::atof(it[2].c_str()), std::atoi(it[3].c_str()));
			}
		}
	}
	catch (std::exception const& e) {
		throw (std::runtime_error(e.what()));
	}
}