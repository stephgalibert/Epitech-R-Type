#include "CommandFactory.hpp"

std::unordered_map<int, std::function<std::shared_ptr<ICommand>(void)> > CommandFactory::Commands = {
	{(int)CommandType::Connect, std::bind(&CommandFactory::cmd_connect)},
	{(int)CommandType::CreateParty, std::bind(&CommandFactory::cmd_createParty)}
};

//CommandFactory::CommandFactory(void)
//{
//	_cmds[(int)CommandType::Connect] = std::bind(&CommandFactory::cmd_connect, this);
//	_cmds[(int)CommandType::CreateParty] = std::bind(&CommandFactory::cmd_createParty, this);
//}
//
//CommandFactory::~CommandFactory(void)
//{
//}

std::shared_ptr<ICommand> CommandFactory::build(CommandType type)
{
	if (Commands.find((int)type) != Commands.cend()) {
		return (Commands.at((int)type)());
	}
	return (NULL);
}

std::shared_ptr<ICommand> CommandFactory::cmd_collision(void)
{
	return std::make_shared<CMDCollision>(); //(new CMDCollision);
}

std::shared_ptr<ICommand> CommandFactory::cmd_connect(void)
{
	return std::make_shared<CMDConnect>(); //(new CMDConnect);
}

std::shared_ptr<ICommand> CommandFactory::cmd_createParty(void)
{
	return std::make_shared<CMDCreateParty>(); //(new CMDCreateParty);
}

std::shared_ptr<ICommand> CommandFactory::cmd_disconnected(void)
{
	return std::make_shared<CMDDisconnected>(); //(new CMDDisconnected);
}

std::shared_ptr<ICommand> CommandFactory::cmd_error(void)
{
	return std::make_shared<CMDError>(); //(new CMDError);
}

std::shared_ptr<ICommand> CommandFactory::cmd_fire(void)
{
	return std::make_shared<CMDFire>(); //(new CMDFire);
}

std::shared_ptr<ICommand> CommandFactory::cmd_move(void)
{
	return std::make_shared<CMDMove>(); //(new CMDMove);
}

std::shared_ptr<ICommand> CommandFactory::cmd_ping(void)
{
	return std::make_shared<CMDPing>(); //(new CMDPing);
}

std::shared_ptr<ICommand> CommandFactory::cmd_spawn(void)
{
	return std::make_shared<CMDSpawn>(); //(new CMDSpawn);
}
