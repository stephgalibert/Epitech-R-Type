#include "LuaHandler.hpp"

LuaHandler::LuaHandler(std::string const& mobName)
{
	_luaFileName = "./rsrc/script/" + mobName + ".lua";
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

void LuaHandler::getMultiTarget(std::pair<double, double> mobPos, 
	std::vector<PlayerData> const& players, 
	std::vector<std::pair<int16_t, int16_t>> & targets, uint16_t nbTarget)
{
	int playerPos[10];
	int result;
	int c;

	if (!players.size())
		return;
	for (int i = 0; i < 10; i++)
		playerPos[i] = -1;
	playerPos[0] = static_cast<int>(mobPos.first);
	playerPos[1] = static_cast<int>(mobPos.second);
	c = 2;
	for (auto const & element : players) {
		playerPos[c] = static_cast<int>(element.x);
		playerPos[c + 1] = static_cast<int>(element.y);
		c += 2;
	}
	for (uint8_t i = 0; i < nbTarget; i++) {
		result = 0;
		_lua->callFunction("getTarget", 10, playerPos, result);
		if (result > static_cast<int>(players.size()))
			return;
		targets[i] = std::make_pair(static_cast<uint16_t>(players[result].x),
			static_cast<uint16_t>(players[result].y));
		c = result * 2 + 2;
		playerPos[c] = -1;
		playerPos[c + 1] = -1;
	}
	for (uint8_t i = 0; i < nbTarget; i++) {
		if (i != 0 && targets[i].first == -1) {
			targets[i].first = targets[i - 1].first;
			targets[i].second = targets[i - 1].second;
		}
	}
}

std::pair<uint16_t, uint16_t> LuaHandler::getTarget(std::pair<double, double> mobPos, std::vector<PlayerData> const& players)
{
	int playerPos[10];
	int result = 0;
	int c;
	static int rand = -1;

	rand += 1;
	if (!players.size())
		return (std::make_pair(0, 0));
	if (rand % 2) {
		int target = _gen(1, players.size()) - 1;		
		return (std::make_pair(static_cast<uint16_t>(players[target].x),
			static_cast<uint16_t>(players[target].y)));
	}
	for (int i = 0; i < 10; i++)
		playerPos[i] = -1;
	playerPos[0] = static_cast<int>(mobPos.first);
	playerPos[1] = static_cast<int>(mobPos.second);
	c = 2;
	for (auto const & element : players) {
		playerPos[c] = static_cast<int>(element.x);
		playerPos[c + 1] = static_cast<int>(element.y);
		c += 2;
	}
	_lua->callFunction("getTarget", 10, playerPos, result);
	if (result > static_cast<int>(players.size()))
		return (std::make_pair(0, 0));
	return (std::make_pair(static_cast<uint16_t>(players[result].x),
			static_cast<uint16_t>(players[result].y)));
}