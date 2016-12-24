#pragma once

#include <string.h>

#include "StaticTools.hpp"
#include "ICommand.hpp"

class CMDSpawnMonster : public ICommand
{
public:
	CMDSpawnMonster(uint16_t id, uint16_t x, uint16_t y, uint8_t health,
					uint16_t velocity, uint8_t angle, std::string const& type);
	CMDSpawnMonster(void);
	virtual ~CMDSpawnMonster(void);

	virtual void loadFromMemory(char const *data);
	virtual size_t getSize(void) const;
	virtual CommandType getCommandType(void) const;
	virtual char *getData(void) const;

private:
	SpawnMonster *_data;
};

