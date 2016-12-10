#include "RequestDestroyed.hpp"
#include "World.hpp"

RequestDestroyed::RequestDestroyed(void)
{
}

RequestDestroyed::~RequestDestroyed(void)
{
}

void RequestDestroyed::execute(IClient &client, std::shared_ptr<ICommand> data,
								std::shared_ptr<ICommand> &toSend)
{
	Destroyed *collision = (Destroyed *)data->getData();
	uint16_t id = collision->id;

	StaticTools::Log << "executing destroyed request : id " << (int)id << std::endl;
	AEntity *entity = World::getEntityByID(id);
	if (entity) {
		entity->destroy();
	}
}