#include "CMDCollision.hpp"

CMDCollision::CMDCollision(uint8_t id_first, uint8_t id_second)
{
	_data = new Collision;
	_data->cmdType = getCommandType();
	_data->id_first = id_first;
	_data->id_second = id_second;
}

CMDCollision::CMDCollision(void)
{
	_data = new Collision;
}

CMDCollision::~CMDCollision(void)
{
	delete (_data);
}

void CMDCollision::loadFromMemory(char const *data)
{
	Collision const* collision = reinterpret_cast<const Collision *>(data);

	_data->cmdType = getCommandType();
	_data->id_first = collision->id_first;
	_data->id_second = collision->id_second;
}

size_t CMDCollision::getSize(void) const
{
	return (sizeof(Collision));
}

CommandType CMDCollision::getCommandType(void) const
{
	return (CommandType::Collision);
}

char const* CMDCollision::getData(void) const
{
	return (reinterpret_cast<const char *>(_data));
}