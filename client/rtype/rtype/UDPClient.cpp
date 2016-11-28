#include "UDPClient.hpp"

UDPClient::UDPClient(std::string const& ip, std::string const& port)
	: _resolver(_io_service),
	  _socket(_io_service, boost::asio::ip::udp::udp::endpoint(boost::asio::ip::udp::udp::v4(), std::atoi(port.c_str()))),
	  _remote(ip),
	  _port(port)
{
}

UDPClient::~UDPClient()
{
}

#include "CMDPing.hpp"
void UDPClient::connect(void)
{
	StaticTools::Log << "Connecting ..." << std::endl;
	boost::asio::ip::udp::udp::resolver::query query(boost::asio::ip::udp::udp::v4(), _remote, _port);

	_sender = *_resolver.resolve(query);
	read();
	write(new CMDPing(100)); // todelete
	StaticTools::Log << "Connected in UDP mod" << std::endl;
}

void UDPClient::write(ICommand *packet)
{
	bool writeInProgress = !_toWrites.empty();

	_toWrites.push(packet);
	if (!writeInProgress) {
		write();
	}
}

void UDPClient::do_write(boost::system::error_code const& ec, size_t)
{
	if (!ec) {
		ICommand *packet = _toWrites.front();
		free(packet);

		_toWrites.pop();
		if (!_toWrites.empty()) {
			write();
		}
	}
}

void UDPClient::read(void)
{
	_socket.async_receive_from(_read.prepare(1024), _sender,
		boost::bind(&UDPClient::do_read, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void UDPClient::do_read(boost::system::error_code const& ec, size_t len)
{
	if (!ec) {
		char const* packet = boost::asio::buffer_cast<char const *>(_read.data());
		_read.consume(len);

		CommandType type = StaticTools::GetPacketType(packet);
		if (type == CommandType::Ping) {

			Ping ping = *((Ping *)packet);
			StaticTools::Log << "received packet type " << (int)ping.cmdType << ": " << ping.time << std::endl;
		}
		
		ICommand *reply = NULL;
		_reqHandler.request(*this, packet, &reply);

		if (reply) {
			write(reply);
		}

		read();
	}
}

void UDPClient::write(void)
{
	ICommand *packet = _toWrites.front();
	
	_socket.async_send_to(boost::asio::buffer(packet->getData(), packet->getSize()), _sender,
		boost::bind(&UDPClient::do_write, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void UDPClient::disconnect(void)
{
	StaticTools::Log << "Disconnecting ..." << std::endl;
	_io_service.stop();
	if (_runThread.joinable()) {
		_runThread.join();
	}
	StaticTools::Log << "Disconnected" << std::endl;
}

void UDPClient::runThread(void)
{
	try {
		_io_service.run();
	}
	catch (std::exception const& e) {
		std::cerr << e.what() << std::endl;
	}
}

void UDPClient::run(void)
{
	_runThread = std::thread(&UDPClient::runThread, this);
}

bool UDPClient::isConnected(void) const
{
	return (true);
}

IClient &UDPClient::operator<<(ICommand *packet)
{
	write(packet);
	return (*this);
}