#pragma once

#include "ICommand.hpp"

class CMDEffect : public ICommand
{
public:
	CMDEffect(void);
	CMDEffect(EffectType type, uint16_t id, bool toAdd);
	virtual ~CMDEffect(void);

	virtual void loadFromMemory(char const *data);
	virtual size_t getSize(void) const;
	virtual CommandType getCommandType(void) const;
	virtual char *getData(void) const;

private:
	Effect *_data;
};

