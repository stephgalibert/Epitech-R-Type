#include "RequestHandler.hpp"
#include "AConnection.hpp"

RequestHandler::RequestHandler(void)
{
}

RequestHandler::~RequestHandler(void)
{
}

void RequestHandler::receive(std::shared_ptr<AConnection> owner,
							 std::shared_ptr<ICommand> received,
							 std::shared_ptr<ICommand> &reply)
{
	if (received) {
		std::unique_ptr<IRequest> request(RequestBuilder::Build(received->getCommandType()));
		if (request) {
			request->execute(owner, received, reply);
		}
	}
}
