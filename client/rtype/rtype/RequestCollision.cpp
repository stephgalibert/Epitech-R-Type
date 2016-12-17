#include "RequestCollision.hpp"
#include "ICommand.hpp"
#include "Laser.hpp"

RequestCollision::RequestCollision(void)
{
}

RequestCollision::~RequestCollision(void)
{
}

void RequestCollision::execute(IClient &client, std::shared_ptr<ICommand> data,
								std::shared_ptr<ICommand> &toSend)
{
  (void)client;
  (void)toSend;
	Collision *collision = (Collision *)data->getData();
	CollisionType type = collision->type;
	uint16_t id1 = collision->id_first;
	uint16_t id2 = collision->id_second;

	AEntity *entity = World::getEntityByID(id1);
	AEntity *entity2 = World::getEntityByID(id2);
	Laser *laser = dynamic_cast<Laser *>(entity);
	if (!laser) {
		if (entity && entity2) {
			entity->applyCollision(type, entity2);
			entity2->applyCollision(type, entity);
		}
	}
}
