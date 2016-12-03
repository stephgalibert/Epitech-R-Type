#include "RequestSpawn.hpp"

RequestSpawn::RequestSpawn()
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

	StaticTools::DeserializePosition(spawn->position, x, y);

	StaticTools::Log << "executing spawn request : id " << (int)id << std::endl;
	if (id < 5) {
		StaticTools::Log << "spawning mate information: " << std::endl
			<< "\tid: " << (int)id << std::endl
			<< "\tx: " << x << " y: " << y << std::endl;
		Mate *mate = World::TheWorld.spawnEntity<Mate>();
		mate->setPosition(x, y);
	}
}