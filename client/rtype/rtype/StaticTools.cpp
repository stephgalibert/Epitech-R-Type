#include "StaticTools.hpp"

std::ofstream StaticTools::Log;

sf::Vector2i StaticTools::GetResolution(void)
{
	return (sf::Vector2i(800, 480));
}

void StaticTools::GetPosition(uint32_t position, uint16_t &x, uint16_t &y)
{
	x = position >> 16;
	y = position << 16;
}

std::string StaticTools::SerializeLoginServer(std::string const& host, std::string const& pwd)
{
	return (host + ";" + pwd);
}

uint32_t StaticTools::SerializePosition(uint16_t x, uint16_t y)
{
	uint32_t position;

	position = x;
	position = position << 16;
	position &= y;

	return (position);
}

CommandType StaticTools::GetPacketType(char *packet)
{
	return (*(CommandType *)(packet));
}