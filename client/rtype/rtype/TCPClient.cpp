#include "TCPClient.hpp"

TCPClient::TCPClient(std::string const& remote, std::string const& port)
	: _timer(_io_service),
	  _resolver(_io_service),
	  _socket(_io_service),
	  _remote(remote),
	  _port(port)
{
	_connected = false;
}

TCPClient::~TCPClient()
{
}

void TCPClient::connect(void)
{
	StaticTools::Log << "Connecting ..." << std::endl;

	boost::asio::ip::tcp::resolver::query query(_remote, _port);
	boost::asio::ip::tcp::resolver::iterator endpoint_it = _resolver.resolve(query);
	boost::asio::async_connect(_socket, endpoint_it,
		boost::bind(&TCPClient::do_connect, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::iterator));
}

void TCPClient::write(ICommand *packet)
{
	bool writeInProgress = !_toWrites.empty();
	_toWrites.push(packet);
	if (!writeInProgress) {
		write();
	}
}

void TCPClient::disconnect(void)
{
	StaticTools::Log << "Disconnecting ..." << std::endl;
	_io_service.stop();
	if (_runThread.joinable()) {
		_runThread.join();
	}
	_connected = false;
	StaticTools::Log << "Disconnected" << std::endl;
}

void TCPClient::run(void)
{
	_runThread = std::thread(&TCPClient::runThread, this);
}

bool TCPClient::isConnected(void) const
{
	return (_connected);
}

IClient &TCPClient::operator<<(ICommand *packet)
{
	write(packet);
	return (*this);
}

void TCPClient::read(void)
{
	boost::asio::async_read(_socket, _read, boost::asio::transfer_at_least(1),
		boost::bind(&TCPClient::do_read, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void TCPClient::write(void)
{
	ICommand *packet = _toWrites.front();
	boost::asio::async_write(_socket, boost::asio::buffer(packet->getData(), packet->getSize()),
	boost::bind(&TCPClient::do_write, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

#include "CMDConnect.hpp"
void TCPClient::do_connect(boost::system::error_code const& ec, boost::asio::ip::tcp::resolver::iterator)
{
	if (!ec) {
		StaticTools::Log << "Connected in TCP mod" << std::endl;
		read();
		write(new CMDConnect("name", "pwd"));
	} else {
		StaticTools::Log << _remote << ":" << _port << "' is inaccessible (" << ec << ")" << std::endl;
		_timer.expires_from_now(boost::posix_time::seconds(5));
		_timer.async_wait(boost::bind(&TCPClient::connect, this));
	}
}

void TCPClient::do_read(boost::system::error_code const& ec, size_t len)
{
	if (!ec) {
		char const* packet = boost::asio::buffer_cast<char const *>(_read.data()); // !
		_read.consume(len);
		
		CommandType type = StaticTools::GetPacketType(packet);
		if (type == CommandType::Error) {
			
			Error ping = *((Error *)packet);
			StaticTools::Log << "received packet type " << (int)ping.cmdType << ": " << (int)ping.code << std::endl;
		}
		ICommand *reply = NULL;
		//_reqHandler.request(*this, packet, &reply);

		if (reply) {
			write(reply);
		}

		if (_connected) {
			read();
		}
	}
	else {
		_connected = false;
		connect();
	}
}

void TCPClient::do_write(boost::system::error_code const& ec, size_t)
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

void TCPClient::runThread(void)
{
	try {
		_io_service.run();
	}
	catch (std::exception const& e) {
		std::cerr << e.what() << std::endl;
	}
}