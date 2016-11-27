#pragma once

#include <fstream>

#include "Protocol.hpp"

class StaticTools
{
public:
	static std::ofstream StaticTools::Log;

	static CommandType GetPacketType(char *packet);
};

