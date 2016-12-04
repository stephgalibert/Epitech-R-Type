#include "RequestMove.hpp"

RequestMove::RequestMove(void)
{
}

RequestMove::~RequestMove(void)
{
}

void RequestMove::execute(IClient &client, std::shared_ptr<ICommand> data,
	std::shared_ptr<ICommand> &toSend)
{
	Move *move = (Move *)data->getData();

	uint8_t id = move->id_tomove;
	uint8_t direction = move->direction;
	uint8_t velocity = move->velocity;

	AEntity *entity = World::TheWorld.getEntityByID(id);
	if (entity) {
		entity->setVelocity(velocity);
		entity->setDirection(direction);
	}
}