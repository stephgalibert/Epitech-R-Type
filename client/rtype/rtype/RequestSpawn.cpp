#include "RequestSpawn.hpp"
#include "GameController.hpp"

RequestSpawn::RequestSpawn(void)
{
}

RequestSpawn::~RequestSpawn(void)
{
}

void RequestSpawn::execute(IClient &client, std::shared_ptr<ICommand> data,
						   std::shared_ptr<ICommand> &toSend)
{
  (void)toSend;
	Spawn *spawn = (Spawn *)data->getData();

	//ObjectType object = spawn->object;
	uint16_t id = spawn->id_tospawn;
	uint16_t x = 0;
	uint16_t y = 0;
	/*uint8_t type = spawn->type;
	  uint8_t effect = spawn->effect;*/
	bool player = spawn->is_player;

	StaticTools::DeserializePosition(spawn->position, x, y);

	StaticTools::Log << "executing spawn request : id " << (int)id << std::endl;
	if (player) {
		GameController *game = client.getGameController();
		if (game) {
			Player *player = World::spawnEntity<Player>();
			player->setID(id);
			player->setPosition(x, y);
			player->setIClient(&client);
			game->setPlayer(player);
			player->setReadyForInit(true);
			game->setReady(true);
		}
	}
	else if (id < 5) {
		StaticTools::Log << "mate information: " << std::endl
			<< "\tid: " << id << std::endl
			<< "x: " << x << " y: " << y << std::endl;
		Mate *mate = World::spawnEntity<Mate>();
		mate->setID(id);
		mate->setPosition(x, y);
		mate->setReadyForInit(true);
	}
}
