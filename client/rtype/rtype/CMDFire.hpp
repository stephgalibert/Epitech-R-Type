#pragma once

#include "ICommand.hpp"

// finish ctor
class CMDFire : public ICommand
{
public:
	CMDFire(MissileType type, uint8_t id, uint16_t x, uint16_t y,
		     uint8_t velocity, uint8_t angle, uint8_t effect);
	CMDFire(void);
	virtual ~CMDFire(void);

	virtual void loadFromMemory(char const *data);
	virtual size_t getSize(void) const;
	virtual CommandType getCommandType(void) const;
	virtual char const* getData(void) const;

private:
	Fire *_data;
};

