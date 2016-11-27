#include "AConnection.hpp"


void AConnection::AsyncRead(std::shared_ptr<ISocket> socket, size_t transferAtLeast,
							std::function<void(char *, size_t)> callback)
{
	ThreadPool::Pool.addTask(new ReadAsyncTask(socket, transferAtLeast, callback));
}

void AConnection::AsyncWrite(std::shared_ptr<ISocket> socket, char *buffer, size_t size,
							 std::function<void(void)> callback)
{
	ThreadPool::Pool.addTask(new WriteAsyncTask(socket, buffer, size, callback));
}

AConnection::AConnection(std::shared_ptr<ISocket> socket, ConnectionManager &cm,
	RequestHandler &rh, PartyManager &pm)
	: _cm(cm),
	  _rh(rh),
	  _pm(pm),
	  _socket(socket),
	  _running(false),
	  _id(0),
	  _ready(false)
{
	std::cout << "new connection" << std::endl;
}

AConnection::~AConnection(void)
{
	std::cout << "connection end" << std::endl;
}

void AConnection::start(void)
{
	_running = true;
	read();
}

void AConnection::close(void)
{
	_running = false;
}

void AConnection::write(ICommand *command)
{
	bool writeInProgress = !_toWrites.empty();
	_toWrites.push(command);
	if (!writeInProgress) {
		write();
	}
}

PartyManager const& AConnection::getPartyManager(void) const
{
	return _pm;
}

RequestHandler const& AConnection::getRequestHandler(void) const
{
	return _rh;
}

std::shared_ptr<Party> AConnection::getCurrentParty(void) const
{
	//return _party;
	return (NULL);
}

void AConnection::setID(int id)
{
	_id = id;
}

void AConnection::read(void)
{
	AsyncRead(_socket, sizeof(CommandType),
		std::bind(&AConnection::do_read, shared_from_this(),
				std::placeholders::_1, std::placeholders::_2));
}

void AConnection::do_read(char *data, size_t size)
{
	StaticTools::Log << "do_read " << size << " bytes" << std::endl;

	if (size > sizeof(CommandType)) {
		
		CommandType type = StaticTools::GetPacketType(data);
		std::cout << "received command type: " << (int)type << std::endl;

		write(new CMDPing(100));

		if (_running) {
			read();
		}
	}
	else {
		_cm.leave(shared_from_this());
	}
}

void AConnection::write(void)
{
	ICommand *packet = _toWrites.front();

	AsyncWrite(_socket, packet->getData(), packet->getSize(),
		std::bind(&AConnection::do_write, shared_from_this()));
}

void AConnection::do_write(void)
{
	std::cout << "finished to write" << std::endl;
}