#include "CMDRespawn.hpp"

CMDRespawn::CMDRespawn(uint16_t id, uint16_t x, uint16_t y, uint8_t life)
{
	_data = new Respawn;
	_data->cmdType = getCommandType();
	_data->id = id;
	_data->position = StaticTools::SerializePosition(x, y);
	_data->life = life;
}

CMDRespawn::CMDRespawn(void)
{
	_data = new Respawn;
}

CMDRespawn::~CMDRespawn(void)
{
	delete (_data);
}

void CMDRespawn::loadFromMemory(char const *data)
{
	Respawn const respawn = *reinterpret_cast<Respawn const *>(data);

	_data->cmdType = getCommandType();
	_data->id = respawn.id;
	_data->position = respawn.position;
	_data->life = respawn.life;
}

size_t CMDRespawn::getSize(void) const
{
	return (sizeof(Respawn));
}

CommandType CMDRespawn::getCommandType(void) const
{
	return (CommandType::Respawn);
}

char *CMDRespawn::getData(void) const
{
	return (reinterpret_cast<char *>(_data));
}