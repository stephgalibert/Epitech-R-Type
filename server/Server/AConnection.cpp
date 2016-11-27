#include "AConnection.hpp"

void AConnection::AsyncRead(std::shared_ptr<ISocket> socket, size_t transferAtLeast,
								std::function<void(char *, size_t)> callback)
{
	ThreadPool::Pool.QueueTask(new ReadAsyncTask(socket, transferAtLeast, callback));
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
	AsyncRead(_socket, sizeof(CommandType), std::bind(&AConnection::do_read, shared_from_this(),
				std::placeholders::_1, std::placeholders::_2));
}

void AConnection::do_read(char *data, size_t size)
{
	if (size > sizeof(CommandType)) {
		CommandType type = StaticTools::GetPacketType(data);
		std::cout << "received command type: " << (int)type << std::endl;

		StaticTools::Log << "do_read " << size << " bytes" << std::endl;

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

}

void AConnection::do_write(void)
{

}