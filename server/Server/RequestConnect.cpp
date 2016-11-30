#include "RequestConnect.hpp"
#include "AConnection.hpp"
#include "PartyManager.hpp"

RequestConnect::RequestConnect(void)
{
}

RequestConnect::~RequestConnect(void)
{
}

void RequestConnect::execute(std::shared_ptr<AConnection> owner, ICommand *received, ICommand **reply)
{
	std::shared_ptr<Party> party = NULL;
	Connect *connect = reinterpret_cast<Connect *>(received->getData());

	std::string data(connect->data, connect->size);
	std::string name = data.substr(0, data.find_first_of(';'));
	std::string pwd = data.substr(name.size() + 1, data.size() - name.size() + 1);

	party = owner->getPartyManager().addConnexion(owner, name, pwd);
	if (party == NULL) {
		*reply = new CMDError(RT_ERROR_NOT_FOUND);
	}
	else {
		owner->setCurrentParty(party);
	}
}