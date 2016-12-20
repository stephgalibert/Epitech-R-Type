#include "CMDSpawnPlayer.hpp"

CMDSpawnPlayer::CMDSpawnPlayer(void)
{
	_data = NULL;
}

CMDSpawnPlayer::CMDSpawnPlayer(uint16_t id, uint16_t x, uint16_t y, uint8_t health,
								bool isPlayer, std::string const& username)
{
	_data = static_cast<SpawnPlayer *>(malloc(sizeof(SpawnPlayer) + username.size() + 1));

	_data->cmdType = getCommandType();
	_data->id = id;
	_data->health = health;
	_data->isPlayer = isPlayer;
	_data->position = StaticTools::SerializePosition(x, y);
	_data->size = static_cast<uint8_t>(username.size());
	
	memcpy(_data->username, username.c_str(), username.size());
}

CMDSpawnPlayer::~CMDSpawnPlayer(void)
{
	if (_data) {
		free(_data);
	}
}

void CMDSpawnPlayer::loadFromMemory(char const *data)
{
	SpawnPlayer const *player = reinterpret_cast<SpawnPlayer const *>(data);

	if (_data) {
		free(_data);
	}
	_data = static_cast<SpawnPlayer *>(malloc(sizeof(SpawnPlayer) + player->size + 1));

	_data->cmdType = getCommandType();
	_data->id = player->id;
	_data->health = player->health;
	_data->isPlayer = player->isPlayer;
	_data->position = player->position;
	_data->size = player->size;

	memcpy(_data->username, player->username, player->size);
}

size_t CMDSpawnPlayer::getSize(void) const
{
	return (sizeof(SpawnPlayer) + _data->size);
}

CommandType CMDSpawnPlayer::getCommandType(void) const
{
	return (CommandType::SpawnPlayer);
}

char *CMDSpawnPlayer::getData(void) const
{
	return (reinterpret_cast<char *>(_data));
}