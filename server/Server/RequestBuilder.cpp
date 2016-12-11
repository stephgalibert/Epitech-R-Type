#include "RequestBuilder.hpp"

RequestBuilder::RequestBuilder(void)
{
	_requests[(int)CommandType::Connect] = std::bind(&RequestBuilder::create_ConnectRequest, this);
	_requests[(int)CommandType::CreateParty] = std::bind(&RequestBuilder::create_CreatePartyRequest, this);
	_requests[(int)CommandType::Move] = std::bind(&RequestBuilder::create_MoveRequest, this);
	_requests[(int)CommandType::Destroyed] = std::bind(&RequestBuilder::create_DestroyedRequest, this);
	_requests[(int)CommandType::Fire] = std::bind(&RequestBuilder::create_FireRequest, this);
	_requests[(int)CommandType::LoadedPowder] = std::bind(&RequestBuilder::create_LoadedPowderRequest, this);
	_requests[(int)CommandType::Collision] = std::bind(&RequestBuilder::create_CollisionRequest, this);
	_requests[(int)CommandType::Respawn] = std::bind(&RequestBuilder::create_RespawnRequest, this);
}

RequestBuilder::~RequestBuilder(void)
{
}

std::unique_ptr<IRequest> RequestBuilder::build(CommandType type) const
{
	if (_requests.find((int)type) != _requests.cend()) {
		return (std::move(_requests.at((int)type)()));
	}
	return (NULL);
}

std::unique_ptr<IRequest> RequestBuilder::create_RespawnRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestRespawn));
}

std::unique_ptr<IRequest> RequestBuilder::create_LoadedPowderRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestLoadedPowder));
}

std::unique_ptr<IRequest> RequestBuilder::create_ConnectRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestConnect));
}

std::unique_ptr<IRequest> RequestBuilder::create_CreatePartyRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestCreateParty));
}

std::unique_ptr<IRequest> RequestBuilder::create_SpawnRequest(void)
{
	return (NULL);
}

std::unique_ptr<IRequest> RequestBuilder::create_MoveRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestMove));
}

std::unique_ptr<IRequest> RequestBuilder::create_CollisionRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestCollision));
}

std::unique_ptr<IRequest> RequestBuilder::create_ErrorRequest(void)
{
	return NULL;
}

std::unique_ptr<IRequest> RequestBuilder::create_PingRequest(void)
{
	return NULL;
}

std::unique_ptr<IRequest> RequestBuilder::create_FireRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestFire));
}

std::unique_ptr<IRequest> RequestBuilder::create_GameStatusRequest(void)
{
	return NULL;
}

std::unique_ptr<IRequest> RequestBuilder::create_DestroyedRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestDestroyed));
}