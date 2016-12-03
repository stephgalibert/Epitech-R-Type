#include "RequestHandler.hpp"

RequestHandler::RequestHandler(void)
{
}

RequestHandler::~RequestHandler(void)
{
}

void RequestHandler::receive(IClient &client, std::shared_ptr<ICommand> received,
							 std::shared_ptr<ICommand> &reply)
{
	if (received) {
		std::unique_ptr<IRequest> request(_builder.build(received->getCommandType()));
		if (request) {
			request->execute(client, received, reply);
		}
	}
}
