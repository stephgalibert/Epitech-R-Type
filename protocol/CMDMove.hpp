#pragma once

#include "ICommand.hpp"

#include "StaticTools.hpp"

class CMDMove : public ICommand
{
public:
	CMDMove(uint16_t id, uint16_t x, uint16_t y, uint16_t velocity, uint8_t direction);
	CMDMove(void);
	virtual ~CMDMove(void);

	virtual void loadFromMemory(char const *data);
	virtual size_t getSize(void) const;
	virtual CommandType getCommandType(void) const;
	virtual char *getData(void) const;

private:
	Move *_data;
};

