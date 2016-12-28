#include "CMDMessage.hpp"

CMDMessage::CMDMessage(std::string const& msg)
{
	_data = (Message *)malloc(sizeof(Message) + msg.size());
	_data->cmdType = getCommandType();
	_data->size = (uint16_t)msg.size();

	memcpy(_data->data, msg.c_str(), msg.size());
}

CMDMessage::CMDMessage(void)
{
	_data = NULL;
}

CMDMessage::~CMDMessage(void)
{
	if (_data) {
		free(_data);
	}
}

void CMDMessage::loadFromMemory(char const *data)
{
	Message const* message = reinterpret_cast<const Message *>(data);

	if (_data) {
		free(_data);
	}
	_data = (Message *)malloc(sizeof(Message) + message->size);
	_data->cmdType = getCommandType();
	_data->size = message->size;

	memcpy(_data->data, message->data, message->size);
}

size_t CMDMessage::getSize(void) const
{
	return (sizeof(Message) + _data->size);
}

CommandType CMDMessage::getCommandType(void) const
{
	return (CommandType::Message);
}

char *CMDMessage::getData(void) const
{
	return (reinterpret_cast<char *>(_data));
}
