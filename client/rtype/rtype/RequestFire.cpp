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

	uint8_t id = fire->id_launcher;

	AEntity *entity = World::TheWorld.getEntityByID(id);
	ANPC *anpc = dynamic_cast<ANPC *>(entity);
	if (anpc) {
		anpc->shoot(*fire);
	}
}