#include "CommandFactory.hpp"

const std::unordered_map<CommandType, std::function<std::shared_ptr<ICommand>(void)>, EnumHash> CommandFactory::Commands = {
	{ CommandType::Connect, std::bind(&CommandFactory::cmd_connect) },
	{ CommandType::CreateParty, std::bind(&CommandFactory::cmd_createParty) },
	{ CommandType::Spawn, std::bind(&CommandFactory::cmd_spawn) },
	{ CommandType::Disconnected, std::bind(&CommandFactory::cmd_disconnected) },
	{ CommandType::Move, std::bind(&CommandFactory::cmd_move) },
	{ CommandType::Collision, std::bind(&CommandFactory::cmd_collision) },
	{ CommandType::Destroyed, std::bind(&CommandFactory::cmd_destroyed) },
	{ CommandType::Fire, std::bind(&CommandFactory::cmd_fire) },
	{ CommandType::Score, std::bind(&CommandFactory::cmd_score) },
	{ CommandType::LoadedPowder, std::bind(&CommandFactory::cmd_loadedPowder) },
	{ CommandType::Respawn, std::bind(&CommandFactory::cmd_respawn) },
	{ CommandType::GetParty, std::bind(&CommandFactory::cmd_getParty)},
	{ CommandType::GameStatus, std::bind(&CommandFactory::cmd_gameStatus) },
	{ CommandType::Message, std::bind(&CommandFactory::cmd_message) },
	{ CommandType::SpawnPowerUp, std::bind(&CommandFactory::cmd_spawnPowerup) },
	{ CommandType::Disconnect, std::bind(&CommandFactory::cmd_disconnect) }
};

std::shared_ptr<ICommand> CommandFactory::Build(CommandType type)
{
	if (Commands.find(type) != Commands.cend()) {
		return (Commands.at(type)());
	}
	return (NULL);
}


std::shared_ptr<ICommand> CommandFactory::cmd_disconnect(void)
{
	return std::make_shared<CMDDisconnect>();
}

std::shared_ptr<ICommand> CommandFactory::cmd_spawnPowerup(void)
{
	return std::make_shared<CMDSpawnPowerUp>();
}

std::shared_ptr<ICommand> CommandFactory::cmd_message(void)
{
	return std::make_shared<CMDMessage>();
}

std::shared_ptr<ICommand> CommandFactory::cmd_gameStatus(void)
{
	return std::make_shared<CMDGameStatus>();
}

std::shared_ptr<ICommand> CommandFactory::cmd_getParty(void)
{
	return std::make_shared<CMDGetParty>();
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
