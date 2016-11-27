#include "StaticTools.hpp"

std::ofstream StaticTools::Log;

CommandType StaticTools::GetPacketType(char *packet)
{
	return (*(CommandType *)(packet));
}