#include "RequestGetParty.hpp"
#include "AConnection.hpp"
#include "PartyManager.hpp"

RequestGetParty::RequestGetParty(void)
{
}

RequestGetParty::~RequestGetParty(void)
{
}

void RequestGetParty::execute(std::shared_ptr<AConnection> owner,
							std::shared_ptr<ICommand> received,
							std::shared_ptr<ICommand> &reply)
{
	(void)received;
	(void)reply;
	for (auto &it : owner->getPartyManager().getParties()) {
		uint8_t nbPlayer = it.second->getNbPlayer();
		bool pwdPresent = !it.second->getPassword().empty();
		bool running = it.second->isRunning();

		owner->sync_write(std::make_shared<CMDGetParty>(it.first, nbPlayer, pwdPresent, running));
	}
}
