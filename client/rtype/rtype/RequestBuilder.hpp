#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

#include <boost/noncopyable.hpp>

#include "Protocol.hpp"
#include "IRequest.hpp"
#include "RequestSpawn.hpp"
#include "RequestDisconnect.hpp"
#include "RequestMove.hpp"
#include "RequestFire.hpp"
#include "RequestPowder.hpp"
#include "RequestDestroyed.hpp"
#include "RequestCollision.hpp"
#include "RequestRespawn.hpp"
#include "RequestGetParty.hpp"

class RequestBuilder : private boost::noncopyable
{
public:
	RequestBuilder(void);
	~RequestBuilder(void);

	std::unique_ptr<IRequest> build(CommandType type) const;

private:
	std::unique_ptr<IRequest> create_GetPartyRequest(void) const;
	std::unique_ptr<IRequest> create_RespawnRequest(void) const;
	std::unique_ptr<IRequest> create_DestroyedRequest(void) const;
	std::unique_ptr<IRequest> create_LoadedPowderRequest(void) const;
	std::unique_ptr<IRequest> create_ConnectRequest(void) const;
	std::unique_ptr<IRequest> create_DisconnectedRequest(void) const;
	std::unique_ptr<IRequest> create_CreatePartyRequest(void) const;
	std::unique_ptr<IRequest> create_SpawnRequest(void) const;
	std::unique_ptr<IRequest> create_MoveRequest(void) const;
	std::unique_ptr<IRequest> create_CollisionRequest(void) const;
	std::unique_ptr<IRequest> create_ErrorRequest(void) const;
	std::unique_ptr<IRequest> create_PingRequest(void) const;
	std::unique_ptr<IRequest> create_FireRequest(void) const;
	std::unique_ptr<IRequest> create_GameStatusRequest(void) const;

	std::unordered_map<int, std::function<std::unique_ptr<IRequest>(void)> > _requests;
};
