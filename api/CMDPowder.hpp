#pragma once

#include "ICommand.hpp"
#include "StaticTools.hpp"

class CMDPowder : public ICommand
{
public:
	CMDPowder(void);
	CMDPowder(uint8_t id, PowderType type);
	virtual ~CMDPowder(void);

	virtual void loadFromMemory(char const *data);
	virtual size_t getSize(void) const;
	virtual CommandType getCommandType(void) const;
	virtual char *getData(void) const;

private:
	LoadedPowder *_data;
};

