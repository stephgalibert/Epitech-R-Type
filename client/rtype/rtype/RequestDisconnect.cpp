#include "RequestDisconnect.hpp"

RequestDisconnect::RequestDisconnect(void)
{
}

RequestDisconnect::~RequestDisconnect(void)
{
}

void RequestDisconnect::execute(IClient &client, std::shared_ptr<ICommand> data,
	std::shared_ptr<ICommand> &toSend)
{
	(void)client;
	(void)toSend;
	Disconnected *disconnected = (Disconnected *)data->getData();
	uint8_t id = disconnected->id;


	StaticTools::Log << "executing disconnected request : id " << (int)id << std::endl;
	AEntity *entity = World::getEntityByID(id);
	if (entity) {
		entity->recycle();
	}
}
