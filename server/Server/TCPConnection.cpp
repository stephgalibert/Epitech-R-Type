#include "TCPConnection.hpp"

void TCPConnection::AsyncRead(std::shared_ptr<ITCPSocket> socket, size_t transferAtLeast,
								std::function<void(char *, size_t)> callback)
{
	ThreadPool::Pool.addTask(new ReadAsyncTask(socket, transferAtLeast, callback));
}

void TCPConnection::AsyncWrite(std::shared_ptr<ITCPSocket> socket, char *buffer, size_t size,
									std::function<void(void)> callback)
{
	ThreadPool::Pool.addTask(new WriteAsyncTask(socket, buffer, size, callback));
}

TCPConnection::TCPConnection(std::shared_ptr<ITCPSocket> socket, ConnectionManager &cm,
								RequestHandler &rh, PartyManager &pm)
	: AConnection(cm, rh, pm),
	  _socket(socket)
{
	std::cout << "new TCP connection" << std::endl;
}

TCPConnection::~TCPConnection(void)
{
	std::cout << "TCP connection end" << std::endl;
}

void TCPConnection::start(void)
{
	setRunning(true);
	read();
}

void TCPConnection::close(void)
{
	setRunning(false);
}

void TCPConnection::write(ICommand *command)
{
	bool writeInProgress = !_toWrites.empty();
	_toWrites.push(command);
	if (!writeInProgress) {
		write();
	}
}

void TCPConnection::read(void)
{
	AsyncRead(_socket, sizeof(CommandType),
		std::bind(&AConnection::do_read, shared_from_this(),
			std::placeholders::_1, std::placeholders::_2));
}

void TCPConnection::do_read(char *received, size_t size)
{
	StaticTools::Log << "do_read " << size << " bytes" << std::endl;

	if (size > sizeof(CommandType)) {
		CommandType type = StaticTools::GetPacketType(received);
		StaticTools::Log << "received command type: " << (int)type << std::endl;

		ICommand *reply = NULL;
		getRequestHandler().receive(shared_from_this(), received, &reply);

		//if (reply) {
		//	write(reply);
		//}

		if (isRunning()) {
			read();
		}
	}
	else {
		getConnectionManager().leave(shared_from_this());
	}
}

void TCPConnection::write(void)
{
	ICommand *packet = _toWrites.front();

	AsyncWrite(_socket, packet->getData(), packet->getSize(),
		std::bind(&AConnection::do_write, shared_from_this()));
}

void TCPConnection::do_write(void)
{
	ICommand *command = _toWrites.front();
	free(command);
	_toWrites.pop();

	if (!_toWrites.empty()) {
		write();
	}
}