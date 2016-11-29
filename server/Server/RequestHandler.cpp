#include "RequestHandler.hpp"
#include "AConnection.hpp"

RequestHandler::RequestHandler(void)
{
}

RequestHandler::~RequestHandler(void)
{
}

void RequestHandler::receive(std::shared_ptr<AConnection> owner, ICommand *received, ICommand **reply)
{
	if (received) {
		std::unique_ptr<IRequest> request(_reqbuilder.build(received->getCommandType()));
		if (request) {
			request->execute(owner, received, reply);
			//ICommand *command = _cmdBuilder.build(type);
			//command->loadFromMemory(received);
			//if (command) {
			//	request->execute(owner, command, reply);
			//}
		}
	}
}
