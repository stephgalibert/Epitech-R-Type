#pragma once

#include "ICommand.hpp"

class CMDScore : public ICommand
{
public:
	CMDScore(void);
	CMDScore(uint16_t id, uint16_t score);
	virtual ~CMDScore(void);

	virtual void loadFromMemory(char const *data);
	virtual size_t getSize(void) const;
	virtual CommandType getCommandType(void) const;
	virtual char *getData(void) const;

private:
	Score *_data;
};

