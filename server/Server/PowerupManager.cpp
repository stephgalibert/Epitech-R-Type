#include "PowerupManager.hpp"
#include "CMDSpawnPowerUp.hpp"

PowerupManager::PowerupManager(ConnectionManager &cm, LevelManager &lm)
	: _cm(cm),
	  _lm(lm)
{
	_delta = 0;
}

PowerupManager::~PowerupManager(void)
{
}

void PowerupManager::init(void)
{
	try {
		std::vector<PowerupInformation> const& info = _lm.getPowerupInformation();
		for (auto &it : info) {
			_powerupInfo.push(it);
		}
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
	}
}

void PowerupManager::update(double delta, uint16_t &nextID)
{
	_delta += delta;

	if (!_powerupInfo.empty()) {
		try {
			PowerupInformation const& info = _powerupInfo.front();
			if (_delta >= info.time) {
				spawnPowerup(info, nextID);
				_powerupInfo.pop();
			}
		}
		catch (std::exception const& e) {
			StaticTools::Log << e.what() << std::endl;
			_powerupInfo.pop();
		}
	}
}

void PowerupManager::spawnPowerup(PowerupInformation const& info, uint16_t &nextID)
{
	if (info.type == "Force") {
		_cm.broadcast(std::make_shared<CMDSpawnPowerUp>(PowerUPsType::Force, nextID, info.x, info.y));
	}
	else if (info.type == "Health") {
		_cm.broadcast(std::make_shared<CMDSpawnPowerUp>(PowerUPsType::Health, nextID, info.x, info.y));
	}
	++nextID;
}