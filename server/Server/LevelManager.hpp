#pragma once

#include <iostream>
#include <string>
#include <stdint.h>
#include <queue>

#include "LevelParser.hpp"
#include "MonsterInformation.hpp"

class LevelManager
{
public:
	LevelManager(void);
	~LevelManager(void);

	void initialize(void);

	void setLevel(uint8_t level);
	uint8_t getLevel(void) const;

	std::vector<MonsterInformation> const& getMonsterInformation(void) const;

private:
	void parseLevel(void);

private:
	uint8_t _currentLevel;
	std::vector<MonsterInformation> _monsters;
};

