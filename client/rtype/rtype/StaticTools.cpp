#include "StaticTools.hpp"

std::ofstream StaticTools::Log;

sf::Vector2i StaticTools::GetResolution(void)
{
	return (sf::Vector2i(1920, 1080));
}

Packet *StaticTools::CreatePacket(PacketType type, std::string const& data)
{
	size_t i = 0;
	Packet *packet = (Packet *)malloc(sizeof(Packet) + (sizeof(char) * data.size() + 1));
	packet->MAGIC = MAGIC_NUMBER;
	packet->type = type;
	packet->size = data.size();
	while (i < data.size()) {
		packet->data[i] = data.at(i);
		++i;
	}
	packet->data[i] = 0;
	return (packet);
}