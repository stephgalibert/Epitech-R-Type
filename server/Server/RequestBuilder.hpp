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

class RequestBuilder
{
public:
	RequestBuilder(void);
	~RequestBuilder(void);

	std::unique_ptr<IRequest> build(CommandType type) const;

private:
	std::unique_ptr<IRequest> create_ConnectRequest(void);
	std::unique_ptr<IRequest> create_CreatePartyRequest(void);
	std::unique_ptr<IRequest> create_SpawnRequest(void);
	std::unique_ptr<IRequest> create_MoveRequest(void);
	std::unique_ptr<IRequest> create_CollisionRequest(void);
	std::unique_ptr<IRequest> create_DestroyedRequest(void);
	std::unique_ptr<IRequest> create_ErrorRequest(void);
	std::unique_ptr<IRequest> create_PingRequest(void);
	std::unique_ptr<IRequest> create_FireRequest(void);
	std::unique_ptr<IRequest> create_GameStatusRequest(void);

	std::unordered_map<int, std::function<std::unique_ptr<IRequest>(void)> > _requests;
};

