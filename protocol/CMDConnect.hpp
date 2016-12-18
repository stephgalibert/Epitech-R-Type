#pragma once

#include <string>

#include "StaticTools.hpp"
#include "ICommand.hpp"

class CMDConnect : public ICommand
{
public:
	CMDConnect(std::string const& username, std::string const& host, std::string const& pwd);
	CMDConnect(void);
	virtual ~CMDConnect(void);

	virtual void loadFromMemory(char const *data);
	virtual size_t getSize(void) const;
	virtual CommandType getCommandType(void) const;
	virtual char *getData(void) const;

private:
	Connect *_data;
};

