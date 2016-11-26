#include "WinServerSocket.hpp"


WinServerSocket::WinServerSocket(SocketType type)
{
	_socket = 0;
	_type = type;
	WSAStartup(MAKEWORD(2, 0), &_wsdata);
}


WinServerSocket::~WinServerSocket(void)
{
	if (_socket < 1)
		closesocket(_socket);
	WSACleanup();
}

void WinServerSocket::init(std::string const & listenHost, short listenPort)
{
	SOCKADDR_IN sin;
	int ret = 0;
	u_long socket_state = 0; // 1 pour non-bloquant

	sin.sin_addr.s_addr = inet_addr(listenHost.c_str());
	sin.sin_family = AF_INET;
	sin.sin_port = htons(listenPort);
	_socket = socket(AF_INET, _type, 0);
	ioctlsocket(_socket, FIONBIO, &socket_state);
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

ISocket *WinServerSocket::accept(void)
{
	ISocket *socket = new WinSocket(static_cast<SocketType>(_type));
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
