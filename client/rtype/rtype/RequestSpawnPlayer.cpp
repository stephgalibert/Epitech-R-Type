#include "RequestSpawnPlayer.hpp"
#include "GameController.hpp"

RequestSpawnPlayer::RequestSpawnPlayer(void)
{
}

RequestSpawnPlayer::~RequestSpawnPlayer(void)
{
}

void RequestSpawnPlayer::execute(IClient &client, std::shared_ptr<ICommand> data,
								 std::shared_ptr<ICommand> &toSend)
{
	(void)toSend;
	SpawnPlayer const *spawn = reinterpret_cast<SpawnPlayer const *>(data->getData());

	uint16_t id = spawn->id;
	uint16_t x = 0;
	uint16_t y = 0;
	uint8_t life = spawn->health;
	std::string username(spawn->username, spawn->size);
	bool isPlayer = spawn->isPlayer;

	StaticTools::DeserializePosition(spawn->position, x, y);

	GameController *game = client.getGameController();
	if (game) {
		if (isPlayer) {
			Player *player = World::spawnEntity<Player>();
			player->setHealth(spawn->health);
			player->setID(id);
			player->setPosition(x, y);
			player->setName(username);
			player->setIClient(&client);
			player->setHealth(life);
			game->setPlayer(player);
			player->setReadyForInit(true);
			game->setReady(true);
		}
		else {
			Mate *mate = World::spawnEntity<Mate>();
			mate->setID(id);
			mate->setPosition(x, y);
			mate->setName(username);
			mate->setHealth(life);
			game->addMate(mate);
			mate->setReadyForInit(true);
		}
	}
}
