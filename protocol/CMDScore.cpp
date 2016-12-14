#include "CMDScore.hpp"

CMDScore::CMDScore(void)
{
	_data = new Score;
}

CMDScore::CMDScore(uint16_t id, uint16_t score)
{
	_data = new Score;
	_data->cmdType = getCommandType();
	_data->id = id;
	_data->score = score;
}

CMDScore::~CMDScore(void)
{
	delete (_data);
}

void CMDScore::loadFromMemory(char const *data)
{
	Score const score = *reinterpret_cast<const Score *>(data);

	_data->cmdType = getCommandType();
	_data->id = score.id;
	_data->score = score.score;
}

size_t CMDScore::getSize(void) const
{
	return (sizeof(Score));
}

CommandType CMDScore::getCommandType(void) const
{
	return (CommandType::Score);
}

char *CMDScore::getData(void) const
{
	return (reinterpret_cast<char *>(_data));
}