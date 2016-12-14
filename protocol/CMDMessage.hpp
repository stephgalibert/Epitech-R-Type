#pragma once

#include <string.h>

#include "ICommand.hpp"

class CMDMessage : public ICommand
{
public:
	CMDMessage(std::string const& msg);
	CMDMessage(void);
	virtual ~CMDMessage(void);

	virtual void loadFromMemory(char const *data);
	virtual size_t getSize(void) const;
	virtual CommandType getCommandType(void) const;
	virtual char *getData(void) const;

private:
	Message *_data;
};

