#pragma once

#include <string>

#include "ICommand.hpp"
#include "Protocol.hpp"
#include "CommandFactory.hpp"

class GameController;
class MainMenuController;

class IClient
{
public:
	virtual ~IClient(void) {}

	virtual void connect(void) = 0;
	virtual void write(std::shared_ptr<ICommand> packet) = 0;
	virtual void disconnect(void) = 0;
	virtual void run(void) = 0;
	virtual void setRemote(std::string const& ip, std::string const& port) = 0;
	virtual bool isConnected(void) const = 0;
	virtual GameController *getGameController(void) const = 0;
	virtual MainMenuController &getMainMenuController(void) = 0;
	virtual IClient &operator<<(std::shared_ptr<ICommand> packet) = 0;
};