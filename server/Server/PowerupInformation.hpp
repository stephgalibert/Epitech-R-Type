#pragma once

#include <string>
#include <stdint.h>

struct PowerupInformation
{
	PowerupInformation(std::string const& type, double time, uint16_t x, uint16_t y)
	{
		this->type = type;
		this->time = time;
		this->x = x;
		this->y = y;
	}

	std::string type;
	double time;
	uint16_t x;
	uint16_t y;
};