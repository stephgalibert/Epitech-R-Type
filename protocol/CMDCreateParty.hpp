#pragma once

#include <string>

#include "StaticTools.hpp"
#include "ICommand.hpp"

class CMDCreateParty : public ICommand
{
public:
	CMDCreateParty(std::string const& host, std::string const& pwd);
	CMDCreateParty(void);
	virtual ~CMDCreateParty(void);

	virtual void loadFromMemory(char const *data);
	virtual size_t getSize(void) const;
	virtual CommandType getCommandType(void) const;
	virtual char *getData(void) const;

private:
	CreateParty *_data;
};

