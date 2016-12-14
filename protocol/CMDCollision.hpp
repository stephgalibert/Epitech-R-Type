#pragma once

#include "ICommand.hpp"

class CMDCollision : public ICommand
{
public:
	CMDCollision(void);
	CMDCollision(CollisionType type, uint16_t id_first, uint16_t id_second);
	virtual ~CMDCollision(void);

	virtual void loadFromMemory(char const *data);
	virtual size_t getSize(void) const;
	virtual CommandType getCommandType(void) const;
	virtual char *getData(void) const;

private:
	Collision *_data;
};

