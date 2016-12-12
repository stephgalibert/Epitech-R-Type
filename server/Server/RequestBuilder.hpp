#pragma once

#include <unordered_map>
#include <functional>
#include <memory>

#include "IRequest.hpp"
#include "CommandType.hpp"

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

class RequestBuilder
{
public:
	RequestBuilder(void);
	~RequestBuilder(void);

	std::unique_ptr<IRequest> build(CommandType type) const;

private:
	std::unique_ptr<IRequest> create_GameStatusRequest(void) const;
	std::unique_ptr<IRequest> create_GetPartyRequest(void) const;
	std::unique_ptr<IRequest> create_RespawnRequest(void) const;
	std::unique_ptr<IRequest> create_LoadedPowderRequest(void) const;
	std::unique_ptr<IRequest> create_ConnectRequest(void) const;
	std::unique_ptr<IRequest> create_CreatePartyRequest(void) const;
	std::unique_ptr<IRequest> create_SpawnRequest(void) const;
	std::unique_ptr<IRequest> create_MoveRequest(void) const;
	std::unique_ptr<IRequest> create_CollisionRequest(void) const;
	std::unique_ptr<IRequest> create_DestroyedRequest(void) const;
	std::unique_ptr<IRequest> create_ErrorRequest(void) const;
	std::unique_ptr<IRequest> create_PingRequest(void) const;
	std::unique_ptr<IRequest> create_FireRequest(void) const;

	std::unordered_map<int, std::function<std::unique_ptr<IRequest>(void)> > _requests;
};

