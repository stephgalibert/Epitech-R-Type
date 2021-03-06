#include "RequestLoadedPowder.hpp"
#include "Party.hpp"

RequestLoadedPowder::RequestLoadedPowder(void)
{
}

RequestLoadedPowder::~RequestLoadedPowder(void)
{
}

void RequestLoadedPowder::execute(std::shared_ptr<AConnection> owner,
								 std::shared_ptr<ICommand> received,
								 std::shared_ptr<ICommand> &reply)
{
	(void)reply;
	std::shared_ptr<Party> party = owner->getCurrentParty();

	if (party) {
		party->broadcast(owner, received);
	}
}