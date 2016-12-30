#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

#include <stdint.h>

class StaticTools
{
public:
	static std::pair<short, short> GetResolution(void);
	static std::string SerializeLoginServer(std::string const& host, std::string const& pwd, std::string const& username = "");
	static uint32_t SerializePosition(uint16_t x, uint16_t y);
	static void DeserializePosition(uint32_t position, uint16_t &x, uint16_t &y);
	static void Sleep(unsigned int milliseconds);
	static void SplitString(std::string const& s, char delim, std::vector<std::string> &elems);

	static std::ofstream Log;

	static float soundVolume;
	static float musicVolume;
};

