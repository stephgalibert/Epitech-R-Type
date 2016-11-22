#pragma once

#include "ICommand.hpp"

class CMDCollision : public ICommand
{
public:
	CMDCollision(void);
	CMDCollision(uint8_t id_first, uint8_t id_second);
	virtual ~CMDCollision(void);

	virtual void loadFromMemory(char const *data);
	virtual size_t getSize(void) const;
	virtual CommandType getCommandType(void) const;
	virtual char const* getData(void) const;

private:
	Collision *_data;
};

