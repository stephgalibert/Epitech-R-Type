#include "CMDSpawnMonster.hpp"

CMDSpawnMonster::CMDSpawnMonster(uint16_t id, uint16_t x, uint16_t y, uint8_t health,
								 uint16_t velocity, uint8_t angle, std::string const& type)
{
	_data = static_cast<SpawnMonster *>(malloc(sizeof(SpawnMonster) + type.size()));

	_data->cmdType = getCommandType();
	_data->id = id;
	_data->position = StaticTools::SerializePosition(x, y);
	_data->health = health;
	_data->velocity = velocity;
	_data->angle = angle;
	_data->size = static_cast<uint8_t>(type.size());
	memcpy(_data->type, type.c_str(), type.size());
}

CMDSpawnMonster::CMDSpawnMonster(void)
{
	_data = NULL;
}

CMDSpawnMonster::~CMDSpawnMonster(void)
{
	if (_data) {
		free (_data);
	}
}

void CMDSpawnMonster::loadFromMemory(char const *data)
{
	SpawnMonster const *spawn = reinterpret_cast<const SpawnMonster *>(data);
	_data = static_cast<SpawnMonster *>(malloc(sizeof(SpawnMonster) + spawn->size));

	_data->cmdType = getCommandType();
	_data->id = spawn->id;
	_data->position = spawn->position;
	_data->health = spawn->health;
	_data->velocity = spawn->velocity;
	_data->angle = spawn->angle;
	_data->size = spawn->size;
	memcpy(_data->type, spawn->type, spawn->size);
}

size_t CMDSpawnMonster::getSize(void) const
{
	return (sizeof(SpawnMonster) + _data->size);
}

CommandType CMDSpawnMonster::getCommandType(void) const
{
	return (CommandType::SpawnMonster);
}

char *CMDSpawnMonster::getData(void) const
{
	return (reinterpret_cast<char *>(_data));
}
