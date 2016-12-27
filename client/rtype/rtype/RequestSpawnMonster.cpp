#include "RequestSpawnMonster.hpp"

RequestSpawnMonster::RequestSpawnMonster(void)
{
}

RequestSpawnMonster::~RequestSpawnMonster(void)
{
}

void RequestSpawnMonster::execute(IClient &client, std::shared_ptr<ICommand> data,
								  std::shared_ptr<ICommand> &toSend)
{
  (void)client;
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

	AEntity *entity = NULL;
	if (type == "Zork") {
		Zork *zork = World::spawnEntity<Zork>();
		entity = zork;
	}
	else if (type == "Dop") {
		Dop *dop = World::spawnEntity<Dop>();
		entity = dop;
	}
	else if (type == "Ravid") {
		Ravid *ravid = World::spawnEntity<Ravid>();
		entity = ravid;
	}

	if (entity) {
		entity->setID(id);
		entity->setPosition(sf::Vector2f(x, y));
		entity->setHealth(health);
		entity->setVelocity(velocity);
		entity->setAngle(static_cast<float>(angle));
		entity->setReadyForInit(true);
	}
}
