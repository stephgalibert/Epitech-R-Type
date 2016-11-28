#include "TCPServer.hpp"

void TCPServer::AsyncAccept(std::shared_ptr<IServerSocket> ss,
							std::function<void(std::shared_ptr<ITCPSocket>)> function)
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
	_ss = std::make_shared<WinServerSocket>();
#else
	_ss = std::make_shared<UnixServerSocket>();
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
}

void TCPServer::close(void)
{
	std::clog << "shuting down TCP server ..." << std::endl;
	getConnectionManager().closeAll();
	std::clog << "TCP server shutdown success" << std::endl;
}

void TCPServer::accept(void)
{
	AsyncAccept(_ss, std::bind(&TCPServer::do_accept, this, std::placeholders::_1));
}

void TCPServer::do_accept(std::shared_ptr<ITCPSocket> socket)
{
	if (socket != NULL) {
		std::shared_ptr<TCPConnection> connection =
			std::make_shared<TCPConnection>(socket, getConnectionManager(),
											getRequestHandler(), getPartyManager());
		connection->start();
		getConnectionManager().add(connection);
	}
	accept();
}