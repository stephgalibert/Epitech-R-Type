#include "CMDPowder.hpp"

CMDPowder::CMDPowder(uint8_t id, PowderType type)
{
	_data = new LoadedPowder;
	_data->cmdType = getCommandType();
	_data->id = id;
	_data->type = type;
}

CMDPowder::CMDPowder(void)
{
	_data = new LoadedPowder;
}

CMDPowder::~CMDPowder(void)
{
	delete (_data);
}

void CMDPowder::loadFromMemory(char const *data)
{
	LoadedPowder const powder = *reinterpret_cast<const LoadedPowder *>(data);

	_data->cmdType = getCommandType();
	_data->id = powder.id;
	_data->type = powder.type;
}

size_t CMDPowder::getSize(void) const
{
	return (sizeof(LoadedPowder));
}

CommandType CMDPowder::getCommandType(void) const
{
	return (CommandType::LoadedPowder);
}

char *CMDPowder::getData(void) const
{
	return (reinterpret_cast<char *>(_data));
}