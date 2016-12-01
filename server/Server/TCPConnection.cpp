#include "TCPConnection.hpp"
#include "PartyManager.hpp"

void TCPConnection::AsyncRead(std::shared_ptr<ITCPSocket> socket, Buffer &buffer,
	size_t transferAtLeast, std::function<void(bool)> callback)
{
	ThreadPool::Pool.addTask(new ReadAsyncTask(socket, buffer, transferAtLeast, callback));
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

void TCPConnection::write(std::shared_ptr<ICommand> command)
{
	_mutex.lock();
	bool writeInProgress = !_toWrites.empty();
	_toWrites.push(command);

	if (!writeInProgress) {
		write();
	}
	_mutex.unlock();
}

void TCPConnection::sync_write(std::shared_ptr<ICommand> command)
{
	_socket->send(command->getData(), command->getSize());
}

void TCPConnection::read(void)
{
	AsyncRead(_socket, _read, sizeof(CommandType),
		std::bind(&AConnection::do_read, shared_from_this(),
				std::placeholders::_1));
}

void TCPConnection::do_read(bool error)
{
	StaticTools::Log << "tcp do_read " << _read.getSize() << " bytes" << std::endl;
	if (error) {
		CommandType type = StaticTools::GetPacketType(_read.getData());
		std::shared_ptr<ICommand> command = CommandFactory::build(type);
		StaticTools::Log << "received command type: " << (int)type << std::endl;

		if (!command) {
			read();
			return;
		}
		command->loadFromMemory(_read.getData());
		_read.consume(command->getSize());
		std::shared_ptr<ICommand> reply = NULL;
		getRequestHandler().receive(shared_from_this(), command, reply);
		if (reply) {
			StaticTools::Log << "writing reply " << (int)reply->getCommandType() << std::endl;
			write(reply);
		}

		if (isRunning()) {
			if (_read.getSize() > 0) {
				do_read(error);
			}
			else {
				read();
			}
		}
		else {
			std::cout << "deleting connection" << std::endl;
		}
	}
	else {
		getConnectionManager().leave(shared_from_this());
		if (getCurrentParty()) {
			getCurrentParty()->removeConnection(shared_from_this());
		}
	}
}

void TCPConnection::write(void)
{
	std::shared_ptr<ICommand> packet = _toWrites.front();

	AsyncWrite(_socket, packet->getData(), packet->getSize(),
		std::bind(&AConnection::do_write, shared_from_this()));
}

void TCPConnection::do_write(void)
{
	_mutex.lock();
	_toWrites.pop();

	if (!_toWrites.empty()) {
		write();
	}
	_mutex.unlock();
}