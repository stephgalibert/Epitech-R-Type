#include "RequestHandler.hpp"

RequestHandler::RequestHandler(void)
{
}

RequestHandler::~RequestHandler(void)
{
}

void RequestHandler::request(IClient &client, char const* received, ICommand **reply)
{
  (void)client;
  (void)received;
  (void)reply;
	if (received) {

		/*StaticTools::Log << "receive packet type '" << (int)received->type
			<< " with data: " << std::string(received->data, received->size) << "'" << std::endl;

		if (received->type != PacketType::PT_Error
			&& received->type != PacketType::PT_Response) {	*/

			/*std::unique_ptr<IRequest> ptr(_builder.create(received->type));
			std::string param(received->data, received->size);
			if (ptr) {
				ptr->execute(client, param, reply);
			}
		}*/
	}
	else {
		//client << client.createPacket(PacketType::PT_Error, BAD_MAGIC);
	}
}
