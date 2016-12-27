#pragma once

#include <memory>

#include "ConnectionManager.hpp"
#include "StaticTools.hpp"
#include "LevelManager.hpp"

#include "PowerupInformation.hpp"

class PowerupManager
{
public:
	PowerupManager(ConnectionManager &cm, LevelManager &lm);
	~PowerupManager(void);

	void init(void);
	void update(double delta, uint16_t &nextID);

private:
	void spawnPowerup(PowerupInformation const& info, uint16_t &nextID);

private:
	ConnectionManager &_cm;
	LevelManager &_lm;
	double _delta;
	std::queue<PowerupInformation> _powerupInfo;
};

