#include "RequestDisconnect.hpp"
#include "Party.hpp"
#include "AConnection.hpp"

RequestDisconnect::RequestDisconnect(void)
{
}

RequestDisconnect::~RequestDisconnect(void)
{
}

void RequestDisconnect::execute(std::shared_ptr<AConnection> owner,
								std::shared_ptr<ICommand> received,
								std::shared_ptr<ICommand> &reply)
{
	(void)reply;
	(void)received;
	std::shared_ptr<Party> party = owner->getCurrentParty();

	if (party) {
		std::cout << "request disconnect" << std::endl;
		party->removeConnection(owner);
	}
}
