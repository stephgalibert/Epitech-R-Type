#include "CommandFactory.hpp"

std::unordered_map<int, std::function<std::shared_ptr<ICommand>(void)> > CommandFactory::Commands = {
	{(int)CommandType::Connect, std::bind(&CommandFactory::cmd_connect)},
	{(int)CommandType::CreateParty, std::bind(&CommandFactory::cmd_createParty)},
	{(int)CommandType::Spawn, std::bind(&CommandFactory::cmd_spawn)},
	{(int)CommandType::Disconnected, std::bind(&CommandFactory::cmd_disconnected)},
	{(int)CommandType::Move, std::bind(&CommandFactory::cmd_move)},
	{(int)CommandType::Collision, std::bind(&CommandFactory::cmd_collision)},
	{(int)CommandType::Destroyed, std::bind(&CommandFactory::cmd_destroyed)},
	{(int)CommandType::Fire, std::bind(&CommandFactory::cmd_fire)},
	{(int)CommandType::Score, std::bind(&CommandFactory::cmd_score)},
	{(int)CommandType::LoadedPowder, std::bind(&CommandFactory::cmd_loadedPowder)},
	{(int)CommandType::Respawn, std::bind(&CommandFactory::cmd_respawn)}
};

std::shared_ptr<ICommand> CommandFactory::build(CommandType type)
{
	if (Commands.find((int)type) != Commands.cend()) {
		return (Commands.at((int)type)());
	}
	return (NULL);
}

std::shared_ptr<ICommand> CommandFactory::cmd_respawn(void)
{
	return std::make_shared<CMDRespawn>();
}

std::shared_ptr<ICommand> CommandFactory::cmd_loadedPowder(void)
{
	return std::make_shared<CMDPowder>();
}

std::shared_ptr<ICommand> CommandFactory::cmd_collision(void)
{
	return std::make_shared<CMDCollision>();
}

std::shared_ptr<ICommand> CommandFactory::cmd_destroyed(void)
{
	return std::make_shared<CMDDestroyed>();
}

std::shared_ptr<ICommand> CommandFactory::cmd_connect(void)
{
	return std::make_shared<CMDConnect>();
}

std::shared_ptr<ICommand> CommandFactory::cmd_createParty(void)
{
	return std::make_shared<CMDCreateParty>();
}

std::shared_ptr<ICommand> CommandFactory::cmd_disconnected(void)
{
	return std::make_shared<CMDDisconnected>();
}

std::shared_ptr<ICommand> CommandFactory::cmd_score(void)
{
	return (std::make_shared<CMDScore>());
}

std::shared_ptr<ICommand> CommandFactory::cmd_error(void)
{
	return std::make_shared<CMDError>();
}

std::shared_ptr<ICommand> CommandFactory::cmd_fire(void)
{
	return std::make_shared<CMDFire>();
}

std::shared_ptr<ICommand> CommandFactory::cmd_move(void)
{
	return std::make_shared<CMDMove>();
}

std::shared_ptr<ICommand> CommandFactory::cmd_ping(void)
{
	return std::make_shared<CMDPing>();
}

std::shared_ptr<ICommand> CommandFactory::cmd_spawn(void)
{
	return std::make_shared<CMDSpawn>();
}
