#pragma once

#include "ICommand.hpp"

class CMDDisconnect : public ICommand
{
public:
	CMDDisconnect(void);
	virtual ~CMDDisconnect(void);

	virtual void loadFromMemory(char const *data);
	virtual size_t getSize(void) const;
	virtual CommandType getCommandType(void) const;
	virtual char *getData(void) const;

private:
	Disconnect *_data;
};

