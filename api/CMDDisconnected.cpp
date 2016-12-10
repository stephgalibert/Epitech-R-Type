#include "CMDDisconnected.hpp"

CMDDisconnected::CMDDisconnected(uint16_t id)
{
	_data = new Disconnected;
	_data->cmdType = getCommandType();
	_data->id = id;
}

CMDDisconnected::CMDDisconnected(void)
{
	_data = new Disconnected;
}

CMDDisconnected::~CMDDisconnected(void)
{
	delete (_data);
}

void CMDDisconnected::loadFromMemory(char const *data)
{
	Disconnected const disconnected = *reinterpret_cast<Disconnected const *>(data);

	_data->cmdType = getCommandType();
	_data->id = disconnected.id;
}

size_t CMDDisconnected::getSize(void) const
{
	return (sizeof(Disconnected));
}

CommandType CMDDisconnected::getCommandType(void) const
{
	return (CommandType::Disconnected);
}

char *CMDDisconnected::getData(void) const
{
	return (reinterpret_cast<char *>(_data));
}