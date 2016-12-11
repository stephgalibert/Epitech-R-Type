#include "RequestRespawn.hpp"
#include "World.hpp"
#include "AShip.hpp"

RequestRespawn::RequestRespawn(void)
{
}

RequestRespawn::~RequestRespawn(void)
{
}

void RequestRespawn::execute(IClient &client, std::shared_ptr<ICommand> data,
							 std::shared_ptr<ICommand> &toSend)
{
	std::cout << "receiving respawn request" << std::endl;
	(void)client;
	(void)toSend;
	Respawn *respawn = (Respawn *)data->getData();

	uint16_t id = respawn->id;
	uint8_t life = respawn->life;
	uint16_t x = 0;
	uint16_t y = 0;

	StaticTools::DeserializePosition(respawn->position, x, y);

	AEntity *entity = World::getEntityByID(id);
	AShip *ship = dynamic_cast<AShip *>(entity);
	if (ship) {
		ship->setPosition(sf::Vector2f((float)x, (float)y));
		ship->setHealth(life);
		ship->respawn();
	}
}