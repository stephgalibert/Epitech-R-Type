#include "CommandFactory.hpp"

CommandFactory::CommandFactory(void)
{
}

CommandFactory::~CommandFactory(void)
{
}

ICommand *CommandFactory::build(CommandType type) const
{
  if (_cmds.find((int)type) != _cmds.cend()) {
    return (_cmds.at((int)type)());
	}
	return (NULL);
}

ICommand *CommandFactory::cmd_collision(void) const
{
	return (new CMDCollision);
}

ICommand *CommandFactory::cmd_connect(void) const
{
	return (new CMDConnect);
}

ICommand *CommandFactory::cmd_createParty(void) const
{
	return (new CMDCreateParty);
}

ICommand *CommandFactory::cmd_disconnected(void) const
{
	return (new CMDDisconnected);
}

ICommand *CommandFactory::cmd_error(void) const
{
	return (new CMDError);
}

ICommand *CommandFactory::cmd_fire(void) const
{
	return (new CMDFire);
}

ICommand *CommandFactory::cmd_move(void) const
{
	return (new CMDMove);
}

ICommand *CommandFactory::cmd_ping(void) const
{
	return (new CMDPing);
}

ICommand *CommandFactory::cmd_spawn(void) const
{
	return (new CMDSpawn);
}
