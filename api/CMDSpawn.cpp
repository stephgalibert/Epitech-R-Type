#include "CMDSpawn.hpp"

CMDSpawn::CMDSpawn(ObjectType object, uint16_t id, uint16_t x, uint16_t y,
	uint8_t type, uint8_t effect, bool player)
{
	_data = new Spawn;
	_data->cmdType = getCommandType();
	_data->object = object;
	_data->id_tospawn = id;
	_data->position = StaticTools::SerializePosition(x, y);
	_data->type = type;
	_data->effect = effect;
	_data->is_player = player;
}

CMDSpawn::CMDSpawn(void)
{
	_data = new Spawn;
}

CMDSpawn::~CMDSpawn(void)
{
	delete (_data);
}

void CMDSpawn::loadFromMemory(char const *data)
{
	Spawn const spawn = *reinterpret_cast<const Spawn *>(data);

	_data->cmdType = getCommandType();
	_data->object = spawn.object;
	_data->id_tospawn = spawn.id_tospawn;
	_data->position = spawn.position;
	_data->type = spawn.type;
	_data->effect = spawn.effect;
	_data->is_player = spawn.is_player;
}

size_t CMDSpawn::getSize(void) const
{
	return (sizeof(Spawn));
}

CommandType CMDSpawn::getCommandType(void) const
{
	return (CommandType::Spawn);
}

char *CMDSpawn::getData(void) const
{
	return (reinterpret_cast<char *>(_data));
}