#pragma once

#include "ICommand.hpp"
#include "StaticTools.hpp"

class CMDRespawn : public ICommand
{
public:
	CMDRespawn(void);
	CMDRespawn(uint16_t id, uint16_t x, uint16_t y, uint8_t life);
	virtual ~CMDRespawn(void);

	virtual void loadFromMemory(char const *data);
	virtual size_t getSize(void) const;
	virtual CommandType getCommandType(void) const;
	virtual char *getData(void) const;

private:
	Respawn *_data;
};

