#include "CMDDestroyed.hpp"

CMDDestroyed::CMDDestroyed(uint16_t id)
{
	_data = new Destroyed;
	_data->cmdType = getCommandType();
	_data->id = id;
}

CMDDestroyed::CMDDestroyed(void)
{
	_data = new Destroyed;
}

CMDDestroyed::~CMDDestroyed(void)
{
	delete (_data);
}

void CMDDestroyed::loadFromMemory(char const *data)
{
	Destroyed const destroyed = *reinterpret_cast<Destroyed const *>(data);

	_data->cmdType = getCommandType();
	_data->id = destroyed.id;
}

size_t CMDDestroyed::getSize(void) const
{
	return (sizeof(Destroyed));
}

CommandType CMDDestroyed::getCommandType(void) const
{
	return (CommandType::Destroyed);
}

char *CMDDestroyed::getData(void) const
{
	return (reinterpret_cast<char *>(_data));
}