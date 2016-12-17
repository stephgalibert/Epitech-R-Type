#include "CMDSpawnPowerUp.hpp"

CMDSpawnPowerUp::CMDSpawnPowerUp(void)
{
	_data = new SpawnPowerUp;
}

CMDSpawnPowerUp::CMDSpawnPowerUp(PowerUPsType type, uint16_t id, uint16_t x, uint16_t y)
{
	_data = new SpawnPowerUp;
	_data->cmdType = getCommandType();
	_data->type = type;
	_data->id = id;
	_data->position = StaticTools::SerializePosition(x, y);
}

CMDSpawnPowerUp::~CMDSpawnPowerUp(void)
{
	delete (_data);
}

void CMDSpawnPowerUp::loadFromMemory(char const *data)
{
	SpawnPowerUp const powerup = *reinterpret_cast<const SpawnPowerUp *>(data);

	_data->cmdType = getCommandType();
	_data->type = powerup.type;
	_data->id = powerup.id;
	_data->position = powerup.position;
}

size_t CMDSpawnPowerUp::getSize(void) const
{
	return (sizeof(SpawnPowerUp));
}

CommandType CMDSpawnPowerUp::getCommandType(void) const
{
	return (CommandType::SpawnPowerUp);
}

char *CMDSpawnPowerUp::getData(void) const
{
	return (reinterpret_cast<char *>(_data));
}