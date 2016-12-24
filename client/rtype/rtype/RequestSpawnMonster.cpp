#include "RequestSpawnMonster.hpp"
#include "World.hpp"
#include "Zork.hpp"

RequestSpawnMonster::RequestSpawnMonster(void)
{
}

RequestSpawnMonster::~RequestSpawnMonster(void)
{
}

void RequestSpawnMonster::execute(IClient &client, std::shared_ptr<ICommand> data,
								  std::shared_ptr<ICommand> &toSend)
{
	(void)toSend;
	SpawnMonster const *spawn = reinterpret_cast<SpawnMonster const *>(data->getData());

	uint16_t id = spawn->id;
	uint16_t x = 0;
	uint16_t y = 0;
	uint8_t health = spawn->health;
	uint16_t velocity = spawn->velocity;
	uint8_t angle = spawn->angle;
	std::string type(spawn->type, spawn->size);

	StaticTools::DeserializePosition(spawn->position, x, y);

	x = StaticTools::GetResolution().first;

	if (type == "Zork") {
		Zork *zork = World::spawnEntity<Zork>();
		zork->setID(id);
		zork->setPosition(sf::Vector2f(x, y));
		zork->setHealth(health);
		zork->setVelocity(velocity);
		zork->setAngle(static_cast<float>(angle));
		zork->setReadyForInit(true);
	}
}
