#include "RequestFire.hpp"
#include "ANPC.hpp"

RequestFire::RequestFire(void)
{
}

RequestFire::~RequestFire(void)
{
}

void RequestFire::execute(IClient &client, std::shared_ptr<ICommand> data,
							std::shared_ptr<ICommand> &toSend)
{
	(void)client;
	(void)toSend;
	Fire *fire = (Fire *)data->getData();

	uint16_t id_launcher = fire->id_launcher;

	AEntity *entity = World::getEntityByID(id_launcher);
	AShip *ship = dynamic_cast<AShip *>(entity);
	if (ship) {
		ship->shoot(*fire);
	}
}