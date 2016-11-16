#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "Protocol.hpp"

class StaticTools
{
public:
	StaticTools(void);
	~StaticTools(void);

	static Packet *CreatePacket(PacketType type, std::string const& data);

	static std::ofstream Log;
};

