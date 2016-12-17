#include "RequestScore.hpp"
#include "World.hpp"
#include "AShip.hpp"

RequestScore::RequestScore(void)
{
}

RequestScore::~RequestScore(void)
{
}

void RequestScore::execute(IClient &client, std::shared_ptr<ICommand> data,
						   std::shared_ptr<ICommand> &toSend)
{
  (void)client;
  (void)toSend;
	Score const *getScore = reinterpret_cast<Score const *>(data->getData());

	uint16_t id = getScore->id;
	uint16_t score = getScore->score;

	AEntity *entity = World::getEntityByID(id);
	if (entity) {
		AShip *ship = dynamic_cast<AShip *>(entity);
		if (ship) {
			ship->setScore(score);
		}
	}
}
