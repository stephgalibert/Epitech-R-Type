#include "RequestGetParty.hpp"
#include "MainMenuController.hpp"

RequestGetParty::RequestGetParty(void)
{
}

RequestGetParty::~RequestGetParty(void)
{
}

void RequestGetParty::execute(IClient &client, std::shared_ptr<ICommand> data,
								std::shared_ptr<ICommand> &toSend)
{
	(void)toSend;
	GetParty const *getParty = reinterpret_cast<GetParty const *>(data->getData());
	
	uint8_t nbPlayer = getParty->nbPlayer;
	bool isRunning = getParty->running;
	bool pwdPresent = getParty->pwdPresent;
	std::string name(getParty->data, getParty->size);

	std::cout << "party received: " << std::endl
		<< "\tname: " << name << std::endl
		<< "\tnbPlayer: " << (int)nbPlayer << std::endl
		<< "\tisRunning: " << isRunning << std::endl
		<< "\tpwdPresent: " << pwdPresent << std::endl;

	 client.getMainMenuController().addBrowserEntry(*getParty);
}