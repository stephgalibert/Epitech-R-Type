#include "CMDPing.hpp"

CMDPing::CMDPing(long unixtime)
{
	_data = new Ping;
	_data->cmdType = getCommandType();
	_data->time = unixtime;
}

CMDPing::CMDPing(void)
{
	_data = new Ping;
}

CMDPing::~CMDPing(void)
{
	delete (_data);
}

void CMDPing::loadFromMemory(char const *data)
{
	Ping const ping = *reinterpret_cast<Ping const *>(data);

	_data->cmdType = getCommandType();
	_data->time = ping.time;
}

size_t CMDPing::getSize(void) const
{
	return (sizeof(Ping));
}

CommandType CMDPing::getCommandType(void) const
{
	return (CommandType::Ping);
}

char *CMDPing::getData(void) const
{
	return (reinterpret_cast<char *>(_data));
}