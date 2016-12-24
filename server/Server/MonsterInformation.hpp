#pragma once

#include <string>
#include <stdint.h>

struct MonsterInformation
{
	MonsterInformation(std::string const& type, double time, uint16_t y)
	{
		this->type = type;
		this->time = time;
		this->y = y;
	}

	std::string type;
	double time;
	uint16_t y;
};
