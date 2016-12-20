#pragma once

#include <string.h>

#include "ICommand.hpp"
#include "StaticTools.hpp"

class CMDSpawnPlayer : public ICommand
{
public:
	CMDSpawnPlayer(void);
	CMDSpawnPlayer(uint16_t id, uint16_t x, uint16_t y, uint8_t health,
					bool isPlayer, std::string const& username);
	virtual ~CMDSpawnPlayer();

	virtual void loadFromMemory(char const *data);
	virtual size_t getSize(void) const;
	virtual CommandType getCommandType(void) const;
	virtual char *getData(void) const;

private:
	SpawnPlayer *_data;
};

