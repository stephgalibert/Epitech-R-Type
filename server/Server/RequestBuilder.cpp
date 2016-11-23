#include "RequestBuilder.h"



RequestBuilder::RequestBuilder() {}


RequestBuilder::~RequestBuilder() {}

IRequest * RequestBuilder::create_SpawnRequest(void) {
	return nullptr;
}

IRequest * RequestBuilder::create_MoveRequest(void) {
	return nullptr;
}

IRequest * RequestBuilder::create_CollisionRequest(void) {
	return nullptr;
}

IRequest * RequestBuilder::create_ErrorRequest(void) {
	return nullptr;
}

IRequest * RequestBuilder::create_PingRequest(void) {
	return nullptr;
}

IRequest * RequestBuilder::create_FireRequest(void) {
	return nullptr;
}

IRequest * RequestBuilder::create_GameStatusRequest(void) {
	return nullptr;
}
