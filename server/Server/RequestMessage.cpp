#include "RequestMessage.hpp"
#include "Party.hpp"

RequestMessage::RequestMessage(void)
{
}

RequestMessage::~RequestMessage(void)
{
}

void RequestMessage::execute(std::shared_ptr<AConnection> owner,
							 std::shared_ptr<ICommand> received,
							 std::shared_ptr<ICommand> &reply)
{
	(void)reply;
	std::shared_ptr<Party> party = owner->getCurrentParty();

	if (party) {
		party->broadcast(received);
	}
}