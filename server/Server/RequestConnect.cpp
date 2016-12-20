#include "RequestConnect.hpp"
#include "AConnection.hpp"
#include "PartyManager.hpp"

RequestConnect::RequestConnect(void)
{
}

RequestConnect::~RequestConnect(void)
{
}

void RequestConnect::execute(std::shared_ptr<AConnection> owner,
							 std::shared_ptr<ICommand> received,
							 std::shared_ptr<ICommand> &reply)
{
	std::shared_ptr<Party> party = NULL;
	Connect const *connect = reinterpret_cast<Connect const *>(received->getData());

	std::string data(connect->data, connect->size);

	std::string name = data.substr(0, data.find_first_of(';'));
#ifdef _WIN32
	std::string room = data.substr(name.size() + 1, data.find_first_of(';'));
#else
	std::string room = data.substr(name.size() + 1, data.find_first_of(';') + 1);
#endif
	std::string pwd = data.substr(data.find_last_of(';') + 1);

	owner->setName(name);
	party = owner->getPartyManager().addConnexion(owner, room, pwd);
	
	if (party == NULL) {
		reply = std::make_shared<CMDError>(RT_ERROR_NOT_FOUND);
	}
	else {
		owner->setCurrentParty(party);
	}
}