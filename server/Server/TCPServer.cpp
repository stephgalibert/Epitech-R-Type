#include "TCPServer.hpp"

void TCPServer::AsyncAccept(std::shared_ptr<IServerSocket> ss,
							std::function<void(std::shared_ptr<ISocket>)> function)
{
	ThreadPool::Pool.addTask(new AcceptAsyncTask(ss, function));
}

TCPServer::TCPServer(ConnectionManager &cm, PartyManager &pm)
	: AServer(cm, pm)
{
}

TCPServer::~TCPServer(void)
{

}

void TCPServer::init(void)
{
#ifdef _WIN32
	_ss = std::make_shared<WinServerSocket>(SocketType::TCP);
#else
	_ss = std::make_shared<UnixServerSocket>(SocketType::TCP);
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
	accept();
	while (true); // manage input ?
}

void TCPServer::close(void)
{
}

void TCPServer::accept(void)
{
	AsyncAccept(_ss, std::bind(&TCPServer::do_accept, this, std::placeholders::_1));
}

void TCPServer::do_accept(std::shared_ptr<ISocket> socket)
{
	if (socket != NULL) {
		std::shared_ptr<AConnection> connection =
			std::make_shared<AConnection>(socket, getConnectionManager(),
											getRequestHandler(), getPartyManager());
		connection->start();
		getConnectionManager().add(connection);
	}
	accept();
}