#include "RequestHandler.hpp"
#include "AConnection.hpp"

RequestHandler::RequestHandler(void)
{
}

RequestHandler::~RequestHandler(void)
{
}

void RequestHandler::receive(std::shared_ptr<AConnection> owner, char *received, ICommand **reply)
{
	if (received) {
		CommandType type = StaticTools::GetPacketType(received);
		std::unique_ptr<IRequest> request(_reqbuilder.build(type));
		if (request) {
			ICommand *command = _cmdBuilder.build(type);
			command->loadFromMemory(received);
			if (command) {
				request->execute(owner, command, reply);
			}
		}
	}
}
