#pragma once

#include <unordered_map>
#include <functional>

#include "Protocol.hpp"

#include "CMDCollision.hpp"
#include "CMDConnect.hpp"
#include "CMDCreateParty.hpp"
#include "CMDDisconnected.hpp"
#include "CMDError.hpp"
#include "CMDFire.hpp"
#include "CMDMove.hpp"
#include "CMDPing.hpp"
#include "CMDSpawn.hpp"
#include "CMDDestroyed.hpp"
#include "CMDScore.hpp"
#include "CMDPowder.hpp"
#include "CMDRespawn.hpp"
#include "CMDGetParty.hpp"
#include "CMDGameStatus.hpp"

class CommandFactory
{
public:
	static std::shared_ptr<ICommand> build(CommandType type);

private:
	static std::shared_ptr<ICommand> cmd_gameStatus(void);
	static std::shared_ptr<ICommand> cmd_getParty(void);
	static std::shared_ptr<ICommand> cmd_respawn(void);
	static std::shared_ptr<ICommand> cmd_loadedPowder(void);
	static std::shared_ptr<ICommand> cmd_collision(void);
	static std::shared_ptr<ICommand> cmd_destroyed(void);
	static std::shared_ptr<ICommand> cmd_connect(void);
	static std::shared_ptr<ICommand> cmd_createParty(void);
	static std::shared_ptr<ICommand> cmd_disconnected(void);
	static std::shared_ptr<ICommand> cmd_score(void);
	static std::shared_ptr<ICommand> cmd_error(void);
	static std::shared_ptr<ICommand> cmd_fire(void);
	static std::shared_ptr<ICommand> cmd_move(void);
	static std::shared_ptr<ICommand> cmd_ping(void);
	static std::shared_ptr<ICommand> cmd_spawn(void);

	static std::unordered_map<int, std::function<std::shared_ptr<ICommand>(void)> > Commands;
};

