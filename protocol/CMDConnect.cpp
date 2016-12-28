#include "CMDConnect.hpp"

CMDConnect::CMDConnect(std::string const& username, std::string const& host, std::string const& pwd)
{
	std::string serial = StaticTools::SerializeLoginServer(host, pwd, username);

	_data = static_cast<Connect *>(malloc(sizeof(Connect) + serial.size() + 1));
	_data->cmdType = getCommandType();
	_data->size = static_cast<uint32_t>(serial.size());

	memcpy(_data->data, serial.c_str(), serial.size());
}

CMDConnect::CMDConnect(void)
{
	_data = NULL;
}

CMDConnect::~CMDConnect(void)
{
	if (_data) {
		free(_data);
	}
}

void CMDConnect::loadFromMemory(char const *data)
{
	Connect const* connect = reinterpret_cast<const Connect *>(data);

	if (_data) {
		free (_data);
	}
	_data = static_cast<Connect *>(malloc(sizeof(Connect) + connect->size + 1));
	_data->cmdType = getCommandType();
	_data->size = connect->size;
	memcpy(_data->data, connect->data, connect->size);
}

size_t CMDConnect::getSize(void) const
{
	return (sizeof(Connect) + _data->size);
}

CommandType CMDConnect::getCommandType(void) const
{
	return (CommandType::Connect);
}

char *CMDConnect::getData(void) const
{
	return (reinterpret_cast<char *>(_data));
}
