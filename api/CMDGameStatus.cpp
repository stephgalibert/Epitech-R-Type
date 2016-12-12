#include "CMDGameStatus.hpp"

CMDGameStatus::CMDGameStatus(GameStatusType status)
{
	_data = new GameStatus;
	_data->cmdType = getCommandType();
	_data->status = status;
}

CMDGameStatus::CMDGameStatus(void)
{
	_data = new GameStatus;
}

CMDGameStatus::~CMDGameStatus(void)
{
	delete (_data);
}

void CMDGameStatus::loadFromMemory(char const *data)
{
	GameStatus const gameStatus = *reinterpret_cast<GameStatus const *>(data);

	_data->cmdType = getCommandType();
	_data->status = gameStatus.status;
}

size_t CMDGameStatus::getSize(void) const
{
	return (sizeof(GameStatus));
}

CommandType CMDGameStatus::getCommandType(void) const
{
	return (CommandType::GameStatus);
}

char *CMDGameStatus::getData(void) const
{
	return (reinterpret_cast<char *>(_data));
}