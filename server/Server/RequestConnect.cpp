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
	Connect *connect = reinterpret_cast<Connect *>(received->getData());
	std::string data(connect->data, connect->size);
	std::string name = data.substr(0, data.find_first_of(';'));
	std::string pwd = data.substr(name.size() + 1, data.size() - name.size() + 1);

	if (owner->getPartyManager().addConnexion(owner, name, pwd) == NULL) {
		*reply = new CMDError(RT_ERROR_NOT_FOUND);
	}
}