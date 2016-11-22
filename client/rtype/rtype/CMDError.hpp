#pragma once

#include "ICommand.hpp"

class CMDError : public ICommand
{
public:
	CMDError(uint8_t code);
	CMDError(void);
	virtual ~CMDError(void);

	virtual void loadFromMemory(char const *data);
	virtual size_t getSize(void) const;
	virtual CommandType getCommandType(void) const;
	virtual char const* getData(void) const;

private:
	Error *_data;
};

