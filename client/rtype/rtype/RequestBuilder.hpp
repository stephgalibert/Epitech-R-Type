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

class RequestBuilder : private boost::noncopyable
{
public:
	RequestBuilder(void);
	~RequestBuilder(void);

	std::unique_ptr<IRequest> build(CommandType type) const;

private:
	std::unique_ptr<IRequest> create_LoadedPowderRequest(void);
	std::unique_ptr<IRequest> create_ConnectRequest(void);
	std::unique_ptr<IRequest> create_DisconnectedRequest(void);
	std::unique_ptr<IRequest> create_CreatePartyRequest(void);
	std::unique_ptr<IRequest> create_SpawnRequest(void);
	std::unique_ptr<IRequest> create_MoveRequest(void);
	std::unique_ptr<IRequest> create_CollisionRequest(void);
	std::unique_ptr<IRequest> create_ErrorRequest(void);
	std::unique_ptr<IRequest> create_PingRequest(void);
	std::unique_ptr<IRequest> create_FireRequest(void);
	std::unique_ptr<IRequest> create_GameStatusRequest(void);

	std::unordered_map<int, std::function<std::unique_ptr<IRequest>(void)> > _requests;
};
