#pragma once

#include "StaticTools.hpp"
#include "ICommand.hpp"

class CMDSpawnPowerUp : public ICommand
{
public:
	CMDSpawnPowerUp(void);
	CMDSpawnPowerUp(PowerUPsType type, uint16_t id, uint16_t x, uint16_t y);
	virtual ~CMDSpawnPowerUp(void);

	virtual void loadFromMemory(char const *data);
	virtual size_t getSize(void) const;
	virtual CommandType getCommandType(void) const;
	virtual char *getData(void) const;

private:
	SpawnPowerUp *_data;
};

