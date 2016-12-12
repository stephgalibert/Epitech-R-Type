#include "CMDGetParty.hpp"

CMDGetParty::CMDGetParty(std::string const& name, uint8_t nbPlayer, bool pwdPresent, bool running)
{
	_data = (GetParty *)malloc(sizeof(GetParty) + name.size() + 1);
	_data->cmdType = getCommandType();
	_data->nbPlayer = nbPlayer;
	_data->pwdPresent = pwdPresent;
	_data->running = running;
	_data->size = (uint8_t)name.size();
	memcpy(_data->data, name.c_str(), name.size());
}

CMDGetParty::CMDGetParty(void)
{
	_data = (GetParty *)malloc(sizeof(GetParty));
	_data->cmdType = getCommandType();
	_data->size = 0;
}

CMDGetParty::~CMDGetParty(void)
{
	if (_data) {
		free(_data);
	}
}

void CMDGetParty::loadFromMemory(char const *data)
{
	GetParty const* getParty = reinterpret_cast<const GetParty *>(data);

	if (_data) {
		free(_data);
	}
	_data = (GetParty *)malloc(sizeof(GetParty) + getParty->size + 1);
	_data->cmdType = getCommandType();
	_data->size = getParty->size;
	_data->nbPlayer = getParty->nbPlayer;
	_data->pwdPresent = getParty->pwdPresent;
	_data->running = getParty->running;
	memcpy(_data->data, getParty->data, getParty->size);
}

size_t CMDGetParty::getSize(void) const
{
	return (sizeof(GetParty) + _data->size);
}

CommandType CMDGetParty::getCommandType(void) const
{
	return (CommandType::GetParty);
}

char *CMDGetParty::getData(void) const
{
	return (reinterpret_cast<char *>(_data));
}