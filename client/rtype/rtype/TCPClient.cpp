#include "TCPClient.hpp"
#include "GameController.hpp"

TCPClient::TCPClient(std::string const& remote, std::string const& port)
	: _timer(_io_service),
	  _resolver(_io_service),
	  _socket(_io_service),
	  _connected(false),
	  _controller(NULL),
	  _remote(remote),
	  _port(port)
{
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

void TCPClient::write(std::shared_ptr<ICommand> packet)
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

void TCPClient::setGameController(GameController *controller)
{
	_controller = controller;
}

GameController *TCPClient::getGameController(void) const
{
	return (_controller);
}

IClient &TCPClient::operator<<(std::shared_ptr<ICommand> packet)
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
	std::shared_ptr<ICommand> packet = _toWrites.front();
	boost::asio::async_write(_socket, boost::asio::buffer(packet->getData(), packet->getSize()),
	boost::bind(&TCPClient::do_write, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

//#include "CMDCreateParty.hpp"
void TCPClient::do_connect(boost::system::error_code const& ec, boost::asio::ip::tcp::resolver::iterator)
{
	if (!ec) {
		StaticTools::Log << "Connected in TCP mod" << std::endl;
		_connected = true;
		read();
		//write(std::make_shared<CMDCreateParty>("name", "pwd"));
	} else {
		StaticTools::Log << _remote << ":" << _port << "' is inaccessible (" << ec << ")" << std::endl;
		_timer.expires_from_now(boost::posix_time::seconds(5));
		_timer.async_wait(boost::bind(&TCPClient::connect, this));
	}
}

void TCPClient::do_read(boost::system::error_code const& ec, size_t len)
{
	StaticTools::Log << "read size: " << len <<  " buffer size: " << _read.size() << std::endl;
	if (!ec) {
		char const* packet = boost::asio::buffer_cast<char const *>(_read.data());
		
		CommandType type = StaticTools::GetPacketType(packet);
		StaticTools::Log << "received packet type: " << (int)type << std::endl;
		std::shared_ptr<ICommand> command = CommandFactory::build(type);

		if (!command) {
			_read.consume(len);
			read();
			return;
		}
		command->loadFromMemory(packet);
		_read.consume(command->getSize());
		std::shared_ptr<ICommand> reply = NULL;
		_reqHandler.receive(*this, command, reply);

		if (reply) {
			write(reply);
		}

		if (_connected) {
			if (_read.size() > 0) {
				do_read(ec, _read.size());
			}
			else {
				read();
			}
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