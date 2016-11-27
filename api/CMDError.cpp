#include "CMDError.hpp"

CMDError::CMDError(uint8_t code)
{
	_data = new Error;
	_data->cmdType = getCommandType();
	_data->code = code;
}

CMDError::CMDError(void)
{
	_data = new Error;
}

CMDError::~CMDError(void)
{
	delete (_data);
}

void CMDError::loadFromMemory(char const *data)
{
	Error const error = *reinterpret_cast<Error const *>(data);

	_data->cmdType = getCommandType();
	_data->code = error.code;
}

size_t CMDError::getSize(void) const
{
	return (sizeof(Error));
}

CommandType CMDError::getCommandType(void) const
{
	return (CommandType::Error);
}

char const* CMDError::getData(void) const
{
	return (reinterpret_cast<const char *>(_data));
}