#include "CMDMove.hpp"

CMDMove::CMDMove(uint16_t id, uint16_t x, uint16_t y, uint16_t velocity, uint8_t direction)
{
	_data = new Move;
	_data->cmdType = getCommandType();
	_data->id_tomove = id;
	_data->position = StaticTools::SerializePosition(x, y);
	_data->direction = direction;
	_data->velocity = velocity;
}

CMDMove::CMDMove(void)
{
	_data = new Move;
}

CMDMove::~CMDMove(void)
{
	delete (_data);
}

void CMDMove::loadFromMemory(char const *data)
{
	Move const move = *reinterpret_cast<Move const *>(data);

	_data->cmdType = getCommandType();
	_data->id_tomove = move.id_tomove;
	_data->direction = move.direction;
	_data->velocity = move.velocity;
	_data->position = move.position;
}

size_t CMDMove::getSize(void) const
{
	return (sizeof(Move));
}

CommandType CMDMove::getCommandType(void) const
{
	return (CommandType::Move);
}

char *CMDMove::getData(void) const
{
	return (reinterpret_cast<char *>(_data));
}