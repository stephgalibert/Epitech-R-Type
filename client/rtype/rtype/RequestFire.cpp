#include "RequestFire.hpp"

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

	MissileType type = fire->type;
	uint8_t id = fire->id_launcher;
	uint16_t x = 0;
	uint16_t y = 0;
	uint8_t velocity = fire->velocity;
	uint8_t angle = fire->angle;
	uint8_t effect = fire->effect;

	StaticTools::DeserializePosition(fire->position, x, y);

	switch (type)
	{
	case MissileType::MT_FriendFire_Lv1:
		Laser *laser = World::TheWorld.spawnEntity<Laser>();
		laser->setPosition(x, y);
		laser->setOwnerID(id);
		laser->setAngle(angle);
		laser->setVelocity(velocity);
		laser->setColor(id);
		laser->setReadyForInit(true);
		break;
	}
}