#include "RequestDisconnect.hpp"
#include "GameController.hpp"

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
