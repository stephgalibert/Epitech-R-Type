#include "UDPConnection.hpp"

void UDPConnection::AsyncReceiveFrom(std::shared_ptr<IUDPSocket> socket, Buffer &buffer,
										Endpoint &endpoint, std::function<void(bool)> callback)
{
	ThreadPool::Pool.addTask(new ReceiveFromAsyncTask(socket, buffer, endpoint, callback));
}

void UDPConnection::AsyncSendTo(std::shared_ptr<IUDPSocket> socket, Endpoint const& endpoint,
									char *data, size_t size, std::function<void(void)> callback)
{
	ThreadPool::Pool.addTask(new SendToAsyncTask(socket, endpoint, data, size, callback));
}

UDPConnection::UDPConnection(ConnectionManager &cm, RequestHandler &rh, PartyManager &pm)
	: AConnection(cm, rh, pm)
{
	std::cout << "new UDP connection" << std::endl;
}

UDPConnection::~UDPConnection(void)
{
	std::cout << "connection UDP end" << std::endl;
}

void UDPConnection::start(void)
{
#ifdef _WIN32
	_socket = std::make_shared<UDPWinSocket>();
#else
	_socket = std::make_shared<UDPUnixSocket>();
#endif
	try {
		_socket->init("127.0.0.1");
		setRunning(true);
		read();
	}
	catch (std::exception const& e) {
		std::cerr << e.what() << std::endl;
	}
}

void UDPConnection::close(void)
{
	setRunning(false);
}

void UDPConnection::write(std::shared_ptr<ICommand> command)
{
	bool write_in_progress = !_toWrites.empty();

	_toWrites.push(command);
	if (!write_in_progress) {
		write();
	}
}

void UDPConnection::sync_write(std::shared_ptr<ICommand> command)
{

}

void UDPConnection::write(void)
{
	std::shared_ptr<ICommand> command = _toWrites.front();

	AsyncSendTo(_socket, _endpoint, command->getData(), command->getSize(),
		std::bind(&AConnection::do_write, shared_from_this()));
}

void UDPConnection::read(void)
{
	AsyncReceiveFrom(_socket, _read, _endpoint,
		std::bind(&AConnection::do_read, shared_from_this(),
					std::placeholders::_1));
}

void UDPConnection::do_write(void)
{
	//std::shared_ptr<ICommand> command = _toWrites.front();
	//free(command);
	_toWrites.pop();
	if (!_toWrites.empty()) {
		write();
	}
}

void UDPConnection::do_read(bool error)
{
	//CommandFactory cmdBuilder;
	// std::cout << "from: " << inet_ntoa(_endpoint.in.sin_addr) << " " << ntohs(_endpoint.in.sin_port) << std::endl;
	StaticTools::Log << "udp do_read " << _read.getSize() << " bytes" << std::endl;

	if (error) {
		
		CommandType type = StaticTools::GetPacketType(_read.getData());
		std::shared_ptr<ICommand> command = CommandFactory::build(type);

		if (!command) {
			read();
			return;
		}
		command->loadFromMemory(_read.getData());
		_read.consume(command->getSize());
		StaticTools::Log << "received command type: " << (int)type << std::endl;
		std::shared_ptr<ICommand> reply = NULL;
		getRequestHandler().receive(shared_from_this(), command, reply);
		if (reply) {
			StaticTools::Log << "writing reply" << std::endl;
			write(reply);
		}
		if (isRunning()) {
			if (_read.getSize() > 0) {
				StaticTools::Log << "recursion" << std::endl;
				do_read(error);
			}
			else {
				read();
			}
		}
	}
	else {
		getConnectionManager().leave(shared_from_this());
	}
}