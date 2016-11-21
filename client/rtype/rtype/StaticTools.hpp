#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include <SFML\Graphics.hpp>

#include "Protocol.hpp"

class StaticTools
{
public:
	static Packet *CreatePacket(PacketType type, std::string const& data);
	static sf::Vector2i GetResolution(void);

	static std::ofstream Log;
};

