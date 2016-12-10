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
	CollisionType type = collision->type;
	uint8_t id1 = collision->id_first;
	uint8_t id2 = collision->id_second;

	AEntity *entity = World::getEntityByID(id1);
	AEntity *entity2 = World::getEntityByID(id2);
	if (entity && entity2) {
		switch (type)
		{
		case CollisionType::None:
			break;
		case CollisionType::Destruction:
			entity->destroy();
			entity2->destroy();
			break;
		case CollisionType::PowerUP:
			break;
		default:
			break;
		}
	}
}