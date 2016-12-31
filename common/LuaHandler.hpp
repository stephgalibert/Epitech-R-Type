#pragma once

#include <string>
#include <vector>
#include <utility>

#include "lua_adapter.hpp"
#include "PlayerData.hpp"
#include "Generator.hpp"

class LuaHandler
{
public:
	LuaHandler(std::string const& mobName);
	~LuaHandler();

	void loadLuaFile(void);
	void closeLuaFile(void);
	std::pair<uint16_t, uint16_t> getTarget(std::pair<double, double> mobPos, std::vector<PlayerData> const& players);
private:
	std::string _luaFileName;
	LuaAdapter *_lua;
	Generator _gen;
};