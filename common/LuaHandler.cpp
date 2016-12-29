#include "LuaHandler.hpp"

LuaHandler::LuaHandler(std::string const& mobName)
{
	_luaFileName = mobName + ".lua";
	loadLuaFile();
}

LuaHandler::~LuaHandler()
{
}

void LuaHandler::loadLuaFile(void)
{
	_lua = new LuaAdapter(this->_luaFileName);
}

void LuaHandler::closeLuaFile(void)
{
	_lua->close();
}

std::pair<uint16_t, uint16_t> LuaHandler::getTarget(void)
{
	int test[] = {36, 24};
	int result = 0;
	_lua->callFunction("getTarget", 2, test, result);
	return (std::make_pair(0, 0));
}