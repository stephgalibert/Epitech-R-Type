#pragma once

#include "ICommand.hpp"

class CMDDisconnected : public ICommand
{
public:
	CMDDisconnected(uint16_t id);
	CMDDisconnected(void);
	virtual ~CMDDisconnected(void);

	virtual void loadFromMemory(char const *data);
	virtual size_t getSize(void) const;
	virtual CommandType getCommandType(void) const;
	virtual char *getData(void) const;

private:
	Disconnected *_data;
};

