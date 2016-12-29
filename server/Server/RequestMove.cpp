#include "RequestMove.hpp"
#include "Party.hpp"

RequestMove::RequestMove(void)
{
}

RequestMove::~RequestMove(void)
{
}


void RequestMove::execute(std::shared_ptr<AConnection> owner,
						  std::shared_ptr<ICommand> received,
						 std::shared_ptr<ICommand> &reply)
{
	(void)reply;
	std::shared_ptr<Party> party = owner->getCurrentParty();

	if (party) {
		//party->broadcast(owner, received);
		party->move(owner, received);
	}
}