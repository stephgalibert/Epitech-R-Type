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
	Spawn *spawn = (Spawn *)data->getData();

	ObjectType object = spawn->object;
	uint8_t id = spawn->id_tospawn;
	uint16_t x = 0;
	uint16_t y = 0;
	uint8_t type = spawn->type;
	uint8_t effect = spawn->effect;
	bool player = spawn->is_player;

	StaticTools::DeserializePosition(spawn->position, x, y);

	StaticTools::Log << "executing spawn request : id " << (int)id << std::endl;
	if (player) {
		Player *player = World::TheWorld.spawnEntity<Player>();
		player->setID(id);
		player->setPosition(x, y);
		player->setIClient(&client);
		client.getGameController()->addPlayer(player);
	}
	else if (id < 5) {
		std::cout << "mate information: " << std::endl
			<< "\tid: " << id << std::endl
			<< "x: " << x << " y: " << y << std::endl;
		Mate *mate = World::TheWorld.spawnEntity<Mate>();
		mate->setID(id);
		mate->setPosition(x, y);
	}
}