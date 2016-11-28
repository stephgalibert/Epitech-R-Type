#include "UDPConnection.hpp"

void UDPConnection::AsyncReceiveFrom(std::shared_ptr<IUDPSocket> socket, Endpoint &endpoint,
										std::function<void(char *, size_t)> callback)
{
	ThreadPool::Pool.addTask(new ReceiveFromAsyncTask(socket, endpoint, callback));
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

void UDPConnection::write(ICommand *command)
{
	bool write_in_progress = !_toWrites.empty();

	_toWrites.push(command);
	if (!write_in_progress) {
		write();
	}
}

void UDPConnection::write(void)
{
	ICommand *command = _toWrites.front();

	AsyncSendTo(_socket, _endpoint, command->getData(), command->getSize(),
		std::bind(&AConnection::do_write, shared_from_this()));
	//Packet *packet = _toWrites.front();
	//_socket.async_send_to(boost::asio::buffer(packet, sizeof(Packet) + packet->size),
	//	_endpoint,
	//	boost::bind(&UDPConnection::do_write, this,
	//		boost::asio::placeholders::error,
	//		boost::asio::placeholders::bytes_transferred));
}

void UDPConnection::read(void)
{
	AsyncReceiveFrom(_socket, _endpoint,
		std::bind(&AConnection::do_read, shared_from_this(),
			std::placeholders::_1, std::placeholders::_2));
}

void UDPConnection::do_write(void)
{
	std::cout << "finished write" << std::endl;
	ICommand *command = _toWrites.front();
	free(command);
	_toWrites.pop();
	if (!_toWrites.empty()) {
		write();
	}
}

void UDPConnection::do_read(char *data, size_t size)
{
	std::cout << "read " << size << " bytes" << std::endl;
	if (size > 0) {
		CommandType type = StaticTools::GetPacketType(data);
		if (type == CommandType::Ping) {

			Ping ping = *((Ping *)data);
			StaticTools::Log << "received packet type " << (int)ping.cmdType << ": " << ping.time << std::endl;

			std::cout << "from: " << inet_ntoa(_endpoint.in.sin_addr) << " " << ntohs(_endpoint.in.sin_port) << std::endl;
		}
		write(new CMDPing(101));
	}
	read();
}