#pragma once

#include <memory>
#include <string>
#include <iostream>

#include "Protocol.hpp"

struct ICommand : public std::enable_shared_from_this<ICommand>
{
	virtual ~ICommand(void) { std::cout << "destroy ICommand" << std::endl; }
	virtual void loadFromMemory(char const *data) = 0;
	virtual size_t getSize(void) const = 0;
	virtual CommandType getCommandType(void) const = 0;
	virtual char *getData(void) const = 0;
};
