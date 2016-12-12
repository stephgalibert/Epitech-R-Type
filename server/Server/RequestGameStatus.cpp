#include "RequestGameStatus.hpp"

RequestGameStatus::RequestGameStatus(void)
{
}

RequestGameStatus::~RequestGameStatus(void)
{
}

void RequestGameStatus::execute(std::shared_ptr<AConnection> owner,
								std::shared_ptr<ICommand> received,
								std::shared_ptr<ICommand> &reply)
{
	(void)reply;
	(void)owner;
	(void)received;
	//std::shared_ptr<Party> party = owner->getCurrentParty();

	//if (party) {
	//	party->fire(received);
	//}
}