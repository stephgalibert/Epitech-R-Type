#include "UnixServerSocket.hpp"
#include "UnixSocket.hpp"

UnixServerSocket::UnixServerSocket(SocketType type)
{
	_type = type;
	_socket = 0;
}


UnixServerSocket::~UnixServerSocket(void)
{
	if (_socket < 1)
		closesocket(_socket);
}

void UnixServerSocket::init(std::string const & listenHost, short listenPort)
{
	SOCKADDR_IN sin;
	int ret = 0;

	sin.sin_addr.s_addr = inet_addr(listenHost.c_str());
	sin.sin_family = AF_INET;
	sin.sin_port = htons(listenPort);
	_socket = socket(AF_INET, _type, 0);
	if (_socket <= 0) {
		throw (std::runtime_error("bad socket"));
	}
	ret = bind(_socket, reinterpret_cast<SOCKADDR *>(&sin), sizeof(sin));
	if (ret < 0) {
		closesocket(_socket);
		_socket = 0;
	}
	ret = listen(_socket, 0);
	if (ret < 0) {
		closesocket(_socket);
		_socket = 0;
	}
}

std::shared_ptr<ISocket> UnixServerSocket::accept(void)
{
	std::shared_ptr<ISocket> socket = std::make_shared<UnixSocket>(_type);
	//ISocket *socket = new UnixSocket(_type);
	SOCKADDR_IN csin;
	SOCKET csock;
	int sinsize;

	sinsize = sizeof(csin);
	if ((csock = ::accept(_socket, (SOCKADDR *)&csin, &sinsize))) {
		socket->connectFromAcceptedFd(csock);
		return (socket);
	}
	return (NULL);
}