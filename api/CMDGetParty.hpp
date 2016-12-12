#pragma once

#include <string>
#include <string.h>

#include "StaticTools.hpp"
#include "ICommand.hpp"

class CMDGetParty : public ICommand
{
public:
	CMDGetParty(std::string const& name, uint8_t nbPlayer, bool pwdPresent, bool running);
	CMDGetParty(void);
	virtual ~CMDGetParty(void);

	virtual void loadFromMemory(char const *data);
	virtual size_t getSize(void) const;
	virtual CommandType getCommandType(void) const;
	virtual char *getData(void) const;

private:
	GetParty *_data;
};

