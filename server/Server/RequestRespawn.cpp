#include "RequestRespawn.hpp"
#include "Party.hpp"

RequestRespawn::RequestRespawn(void)
{
}


RequestRespawn::~RequestRespawn(void)
{
}

void RequestRespawn::execute(std::shared_ptr<AConnection> owner,
							 std::shared_ptr<ICommand> received,
							 std::shared_ptr<ICommand> &reply)
{
	(void)reply;
	std::shared_ptr<Party> party = owner->getCurrentParty();

	if (party) {
		party->respawn(received);
	}
}