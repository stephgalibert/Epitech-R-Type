#include "RequestDisconnected.hpp"
#include "GameController.hpp"

RequestDisconnected::RequestDisconnected(void)
{
}

RequestDisconnected::~RequestDisconnected(void)
{
}

void RequestDisconnected::execute(IClient &client, std::shared_ptr<ICommand> data,
	std::shared_ptr<ICommand> &toSend)
{
	(void)client;
	(void)toSend;
	Disconnected *disconnected = (Disconnected *)data->getData();
	uint16_t id = disconnected->id;

	AEntity *entity = World::getEntityByID(id);
	if (entity) {
		entity->recycle();
	}

	GameController *game = client.getGameController();
	if (game) {
		game->removeMate(id);
	}
}
