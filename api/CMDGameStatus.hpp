#pragma once

#include "ICommand.hpp"

class CMDGameStatus : public ICommand
{
public:
	CMDGameStatus(void);
	CMDGameStatus(GameStatusType type);
	virtual ~CMDGameStatus(void);

	virtual void loadFromMemory(char const *data);
	virtual size_t getSize(void) const;
	virtual CommandType getCommandType(void) const;
	virtual char *getData(void) const;

private:
	GameStatus *_data;
};

