#pragma once

#include "ICommand.hpp"

class CMDPing : public ICommand
{
public:
	CMDPing(long unixtime);
	CMDPing(void);
	virtual ~CMDPing(void);

	virtual void loadFromMemory(char const *data);
	virtual size_t getSize(void) const;
	virtual CommandType getCommandType(void) const;
	virtual char *getData(void) const;

private:
	Ping *_data;
};

