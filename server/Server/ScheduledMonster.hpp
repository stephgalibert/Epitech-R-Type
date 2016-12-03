#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <sstream>

class ScheduledMonster
{
public:
	ScheduledMonster(void);
	~ScheduledMonster(void);

	void loadLevel(size_t level);

private:
	std::list<std::pair<float, std::string>> _schedule;
};

