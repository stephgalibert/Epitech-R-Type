#pragma once

#include "ICommand.hpp"

class CMDDestroyed : public ICommand
{
public:
	CMDDestroyed(uint16_t id);
	CMDDestroyed(void);
	virtual ~CMDDestroyed(void);

	virtual void loadFromMemory(char const *data);
	virtual size_t getSize(void) const;
	virtual CommandType getCommandType(void) const;
	virtual char *getData(void) const;

private:
	Destroyed *_data;
};

