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
	(void)client;
	(void)toSend;
	Move *move = (Move *)data->getData();

	uint16_t id = move->id_tomove;
	uint8_t direction = move->direction;
	uint16_t velocity = move->velocity;
	uint16_t x = 0;
	uint16_t y = 0;

	StaticTools::DeserializePosition(move->position, x, y);

	AEntity *entity = World::getEntityByID(id);
	if (entity) {
		entity->setPosition(x, y);
		entity->setVelocity(velocity);
		entity->setDirection(direction);
	}
}
