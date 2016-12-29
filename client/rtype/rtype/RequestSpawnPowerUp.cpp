#include "RequestSpawnPowerUp.hpp"
#include "World.hpp"

RequestSpawnPowerUp::RequestSpawnPowerUp(void)
{
}

RequestSpawnPowerUp::~RequestSpawnPowerUp(void)
{
}

void RequestSpawnPowerUp::execute(IClient &client, std::shared_ptr<ICommand> data,
								  std::shared_ptr<ICommand> &toSend)
{
	(void)client;
	(void)toSend;
	SpawnPowerUp *spawnpowerup = (SpawnPowerUp *)data->getData();

	PowerUPsType type = spawnpowerup->type;
	uint16_t id = spawnpowerup->id;
	uint16_t x = 0;
	uint16_t y = 0;

	StaticTools::DeserializePosition(spawnpowerup->position, x, y);

	APowerUp *powerup = NULL;
	switch (type)
	{
	case PowerUPsType::Standard:
		break;
	case PowerUPsType::IncreaseNumberOfCanon:
		powerup = World::spawnEntity<Force>();
		break;
	default:
		break;
	}

	if (powerup) {
		std::cout << "spawn power up with ID " << id << std::endl;
		powerup->setID(id);
		powerup->setPosition(sf::Vector2f(x, y));
		powerup->setReadyForInit(true);
	}
}