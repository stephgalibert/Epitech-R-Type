#pragma once

#include <string>

#include "ICommand.hpp"
#include "Protocol.hpp"
#include "CommandFactory.hpp"

class AController;

class IClient
{
public:
	virtual ~IClient(void) {}

	virtual void connect(void) = 0;
	virtual void write(std::shared_ptr<ICommand> packet) = 0;
	virtual void disconnect(void) = 0;
	virtual void run(void) = 0;
	virtual bool isConnected(void) const = 0;
	virtual void setCurrentController(AController *controller) = 0;
	virtual AController *getCurrentController(void) const = 0;
	virtual IClient &operator<<(std::shared_ptr<ICommand> packet) = 0;
};