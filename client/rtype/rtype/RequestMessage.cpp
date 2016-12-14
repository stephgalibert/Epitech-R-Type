#include "RequestMessage.hpp"
#include "GameController.hpp"

RequestMessage::RequestMessage(void)
{
}

RequestMessage::~RequestMessage(void)
{
}


void RequestMessage::execute(IClient &client, std::shared_ptr<ICommand> data,
							 std::shared_ptr<ICommand> &toSend)
{
	(void)client;
	(void)toSend;
	Message const *message = reinterpret_cast<Message const *>(data->getData());

	GameController *game = client.getGameController();
	if (game) {
		game->displayMessage(std::string(message->data, message->size));
	}
}