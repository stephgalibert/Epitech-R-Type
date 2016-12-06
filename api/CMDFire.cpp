#include "CMDFire.hpp"

CMDFire::CMDFire(MissileType type, uint8_t id, uint16_t x, uint16_t y,
	uint8_t velocity, uint8_t angle, uint8_t effect, uint8_t level)
{
	_data = new Fire;
	_data->cmdType = getCommandType();
	_data->type = type;
	_data->id_launcher = id;
	_data->position = StaticTools::SerializePosition(x, y);
	_data->velocity = velocity;
	_data->angle = angle;
	_data->effect = effect;
	_data->level = level;
}

CMDFire::CMDFire(void)
{
	_data = new Fire;
}

CMDFire::~CMDFire(void)
{
	delete (_data);
}

void CMDFire::loadFromMemory(char const *data)
{
	Fire const fire = *reinterpret_cast<const Fire *>(data);

	_data->cmdType = getCommandType();
	_data->type = fire.type;
	_data->id_launcher = fire.id_launcher;
	_data->position = fire.position;
	_data->velocity = fire.velocity;
	_data->angle = fire.angle;
	_data->effect = fire.effect;
	_data->level = fire.level;
}

size_t CMDFire::getSize(void) const
{
	return (sizeof(Fire));
}

CommandType CMDFire::getCommandType(void) const
{
	return (CommandType::Fire);
}

char *CMDFire::getData(void) const
{
	return (reinterpret_cast<char *>(_data));
}