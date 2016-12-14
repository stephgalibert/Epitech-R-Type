#pragma once

#include <iostream>
#include <string>
#include <fstream>

class StaticTools
{
public:
	static std::pair<short, short> GetResolution(void);
	//static CommandType GetPacketType(char const *packet);
	static std::string SerializeLoginServer(std::string const& host, std::string const& pwd);
	static uint32_t SerializePosition(uint16_t x, uint16_t y);
	static void DeserializePosition(uint32_t position, uint16_t &x, uint16_t &y);
	static void sleep(unsigned int milliseconds);

	static std::ofstream Log;
};

