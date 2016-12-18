#pragma once

#include <unordered_map>
#include <functional>
#include <memory>

#include "IRequest.hpp"
#include "CommandType.hpp"
#include "EnumHash.hpp"

#include "RequestConnect.hpp"
#include "RequestCreateParty.hpp"
#include "RequestMove.hpp"
#include "RequestCollision.hpp"
#include "RequestDestroyed.hpp"
#include "RequestFire.hpp"
#include "RequestLoadedPowder.hpp"
#include "RequestRespawn.hpp"
#include "RequestGetParty.hpp"
#include "RequestGameStatus.hpp"
#include "RequestMessage.hpp"
#include "RequestScore.hpp"
#include "RequestDisconnect.hpp"

class RequestBuilder
{
public:
	static std::unique_ptr<IRequest> Build(CommandType type);

private:
	static std::unique_ptr<IRequest> create_DisconnectRequest(void);
	static std::unique_ptr<IRequest> create_ScoreRequest(void);
	static std::unique_ptr<IRequest> create_MessageRequest(void);
	static std::unique_ptr<IRequest> create_GameStatusRequest(void);
	static std::unique_ptr<IRequest> create_GetPartyRequest(void);
	static std::unique_ptr<IRequest> create_RespawnRequest(void);
	static std::unique_ptr<IRequest> create_LoadedPowderRequest(void);
	static std::unique_ptr<IRequest> create_ConnectRequest(void);
	static std::unique_ptr<IRequest> create_CreatePartyRequest(void);
	static std::unique_ptr<IRequest> create_SpawnRequest(void);
	static std::unique_ptr<IRequest> create_MoveRequest(void);
	static std::unique_ptr<IRequest> create_CollisionRequest(void);
	static std::unique_ptr<IRequest> create_DestroyedRequest(void);
	static std::unique_ptr<IRequest> create_ErrorRequest(void);
	static std::unique_ptr<IRequest> create_PingRequest(void);
	static std::unique_ptr<IRequest> create_FireRequest(void);

	static const std::unordered_map<CommandType, std::function<std::unique_ptr<IRequest>(void)>, EnumHash> Requests;
};