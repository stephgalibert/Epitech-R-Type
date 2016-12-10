#include "RequestDestroyed.hpp"
#include "Party.hpp"

RequestDestroyed::RequestDestroyed(void)
{
}

RequestDestroyed::~RequestDestroyed(void)
{
}

void RequestDestroyed::execute(std::shared_ptr<AConnection> owner,
								std::shared_ptr<ICommand> received,
								std::shared_ptr<ICommand> &reply)
{
	(void)reply;
	std::shared_ptr<Party> party = owner->getCurrentParty();
	
	if (party) {
		StaticTools::Log << "executing destroyed request" << std::endl;
		party->broadcast(received);
	}
}