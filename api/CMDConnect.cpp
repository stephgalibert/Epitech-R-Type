#include "CMDConnect.hpp"

CMDConnect::CMDConnect(std::string const& host, std::string const& pwd)
{
	std::string serial = StaticTools::SerializeLoginServer(host, pwd);
	size_t i = 0;

	_data = (Connect *)malloc(sizeof(Connect) + serial.size() + 1);
	_data->cmdType = getCommandType();
	_data->size = (uint16_t)serial.size();

	while (i < serial.size()) {
		_data->data[i] = serial.at(i);
		++i;
	}
	_data->data[i] = 0;
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
	size_t i = 0;
	Connect const* connect = reinterpret_cast<const Connect *>(data);

	if (_data) {
		free (_data);
	}
	_data = (Connect *)malloc(sizeof(Connect) + connect->size + 1);
	_data->cmdType = getCommandType();
	_data->size = connect->size;
	while (i < connect->size) {
		_data->data[i] = connect->data[i];
		++i;
	}
	_data->data[i] = 0;
}

size_t CMDConnect::getSize(void) const
{
	return (sizeof(Connect) + _data->size);
}

CommandType CMDConnect::getCommandType(void) const
{
	return (CommandType::Connect);
}

char const* CMDConnect::getData(void) const
{
	return (reinterpret_cast<const char *>(_data));
}