#include "TCPServer.hpp"

void TCPServer::AsyncAccept(IServerSocket *ss, std::function<void(ISocket *)> function)
{
	ThreadPool::Pool.QueueTask(new AcceptAsyncTask(ss, function));
}

TCPServer::TCPServer(PartyManager &pm)
	: AServer(pm)
{
}

TCPServer::~TCPServer(void)
{

}

void TCPServer::init(void)
{
#ifdef _WIN32
	_ss = new WinServerSocket(SocketType::TCP);
#else
	_ss = new UnixServerSocket(SocketType::TCP);
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
	
}

void TCPServer::accept(void)
{
	AsyncAccept(_ss, std::bind(&TCPServer::do_accept, this, std::placeholders::_1));
}

void TCPServer::do_accept(ISocket *socket)
{
	StaticTools::Log << "do_accept" << std::endl;
	accept();
}