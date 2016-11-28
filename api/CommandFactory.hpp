#pragma once

#include <unordered_map>
#include <functional>

#include "Protocol.hpp"

#include "CMDCollision.hpp"
#include "CMDConnect.hpp"
#include "CMDCreateParty.hpp"
#include "CMDDisconnected.hpp"
#include "CMDError.hpp"
#include "CMDFire.hpp"
#include "CMDMove.hpp"
#include "CMDPing.hpp"
#include "CMDSpawn.hpp"

class CommandFactory
{
public:
	CommandFactory();
	~CommandFactory(void);

	ICommand *build(CommandType type) const;

private:
	ICommand *cmd_collision(void) const;
	ICommand *cmd_connect(void) const;
	ICommand *cmd_createParty(void) const;
	ICommand *cmd_disconnected(void) const;
	ICommand *cmd_error(void) const;
	ICommand *cmd_fire(void) const;
	ICommand *cmd_move(void) const;
	ICommand *cmd_ping(void) const;
	ICommand *cmd_spawn(void) const;

	std::unordered_map<int, std::function<ICommand *(void)> > _cmds;
};

