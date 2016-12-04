#include "RequestCollision.hpp"

RequestCollision::RequestCollision(void)
{
}

RequestCollision::~RequestCollision(void)
{
}

void RequestCollision::execute(IClient &client, std::shared_ptr<ICommand> data,
								std::shared_ptr<ICommand> &toSend)
{
	Collision *collision = (Collision *)data->getData();
	uint8_t id1 = collision->id_first;
	uint8_t id2 = collision->id_second;

	StaticTools::Log << "executing collision request : id " << (int)id1 << " _ " << (int)id2 << std::endl;
	AEntity *entity = World::TheWorld.getEntityByID(id1);
	if (entity) {
		entity->recycle();
	}
}