#include "TCPServer.hpp"

TCPServer::TCPServer(PartyManager &pm)
	: AServer(pm), _ss(NULL)
{
}

TCPServer::~TCPServer(void)
{
	if (_ss) {
		delete (_ss);
	}
}

void TCPServer::init(void)
{
#ifdef _WIN32
	_ss = new WinServerSocket(SocketType::TCP);
#else
	_ss = new UnixServerSocket(SocketType::UDP);
#endif
	try {
		_ss->init("127.0.0.1", 4242);
	}
	catch (std::exception const& e) {
		throw (std::runtime_error(e.what()));
	}
}

void TCPServer::open(void)
{
	ISocket *socket = _ss->accept();

	if (socket != NULL) {

	}
}

void TCPServer::close(void)
{
	
}