#include "RequestCreateParty.hpp"
#include "AConnection.hpp"
#include "PartyManager.hpp"

RequestCreateParty::RequestCreateParty(void)
{
}

RequestCreateParty::~RequestCreateParty(void)
{
}

void RequestCreateParty::execute(std::shared_ptr<AConnection> owner,
								 std::shared_ptr<ICommand> received,
								 std::shared_ptr<ICommand> &reply)
{
	CreateParty *connect = reinterpret_cast<CreateParty *>(received->getData());
	std::string data(connect->data, connect->size);
	std::string name = data.substr(0, data.find_first_of(';'));
	std::string pwd = data.substr(name.size() + 1, data.size() - name.size() + 1);

	try {
		owner->getPartyManager().addParty(name, pwd);
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
		//*reply = new CMDError(RT_ERROR_ALREADY_EXIST);
		reply = std::make_shared<CMDError>(RT_ERROR_ALREADY_EXIST);
	}
}