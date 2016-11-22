#pragma once

#include <string>

#include "ICommand.hpp"
#include "Protocol.hpp"

class IClient
{
public:
	virtual ~IClient(void) {}

	virtual void connect(void) = 0;
	//virtual void write(char *packet) = 0;
	virtual void write(ICommand *packet) = 0;
	virtual void disconnect(void) = 0;
	virtual void run(void) = 0;
	virtual bool isConnected(void) const = 0;
	//virtual IClient &operator<<(char *packet) = 0;
	virtual IClient &operator<<(ICommand *packet) = 0;
};