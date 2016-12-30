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

std::pair<uint16_t, uint16_t> LuaHandler::getTarget(std::pair<double, double> mobPos, std::vector<PlayerData> const& players)
{
	int playerPos[10];
	int result = 0;
	int c;

	if (!players.size())
		return (std::make_pair(0, 0));
	for (int i = 0; i < 10; i++)
		playerPos[i] = -1;
	playerPos[0] = static_cast<int>(mobPos.first);
	playerPos[1] = static_cast<int>(mobPos.second);
	c = 2;
	for (auto & element : players) {
		playerPos[c] = static_cast<int>(element.x);
		playerPos[c + 1] = static_cast<int>(element.y);
		c += 2;
	}
	_lua->callFunction("getTarget", 10, playerPos, result);
	if (result > static_cast<int>(players.size()))
		return (std::make_pair(0, 0));
	return (std::make_pair(static_cast<uint16_t>(players[result].x),
			static_cast<int>(players[result].y)));
}