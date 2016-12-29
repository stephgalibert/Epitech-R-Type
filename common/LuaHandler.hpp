#pragma once

#include "lua_adapter.hpp"
#include <string>
#include <set>
#include <utility>

class LuaHandler
{
public:
	LuaHandler(std::string const& mobName);
	~LuaHandler();

	void loadLuaFile(void);
	void closeLuaFile(void);
	std::pair<uint16_t, uint16_t> getTarget(void);
private:
	std::string _luaFileName;
	LuaAdapter *_lua;
};