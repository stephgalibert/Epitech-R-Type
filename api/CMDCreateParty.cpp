#include "CMDCreateParty.hpp"

CMDCreateParty::CMDCreateParty(std::string const& host, std::string const& pwd)
{
	std::string serial = StaticTools::SerializeLoginServer(host, pwd);
	size_t i = 0;

	_data = (CreateParty *)malloc(sizeof(CreateParty) + host.size() + pwd.size() + 2);
	_data->cmdType = getCommandType();
	_data->size = (uint16_t)serial.size();

	while (i < serial.size()) {
		_data->data[i] = serial.at(i);
		++i;
	}
	_data->data[i] = 0;
}


CMDCreateParty::CMDCreateParty(void)
{
	_data = NULL;
}

CMDCreateParty::~CMDCreateParty(void)
{
	if (_data) {
		free(_data);
	}
}

void CMDCreateParty::loadFromMemory(char const *data)
{
	size_t i = 0;
	CreateParty const* party = reinterpret_cast<const CreateParty *>(data);

	if (_data) {
		free(_data);
	}
	_data = (CreateParty *)malloc(sizeof(CreateParty) + party->size + 1);
	_data->cmdType = getCommandType();
	_data->size = party->size;
	while (i < party->size) {
		_data->data[i] = party->data[i];
		++i;
	}
	_data->data[i] = 0;
}

size_t CMDCreateParty::getSize(void) const
{
	return (sizeof(CreateParty) + _data->size);
}

CommandType CMDCreateParty::getCommandType(void) const
{
	return (CommandType::CreateParty);
}

char const* CMDCreateParty::getData(void) const
{
	return (reinterpret_cast<const char *>(_data));
}