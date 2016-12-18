#include "CMDDisconnect.hpp"

CMDDisconnect::CMDDisconnect(void)
{
	_data = new Disconnect;
	_data->cmdType = getCommandType();
}

CMDDisconnect::~CMDDisconnect(void)
{
	delete (_data);
}

void CMDDisconnect::loadFromMemory(char const *data)
{
	(void)data;

	_data->cmdType = getCommandType();
}

size_t CMDDisconnect::getSize(void) const
{
	return (sizeof(Disconnect));
}

CommandType CMDDisconnect::getCommandType(void) const
{
	return (CommandType::Disconnect);
}

char *CMDDisconnect::getData(void) const
{
	return (reinterpret_cast<char *>(_data));
}