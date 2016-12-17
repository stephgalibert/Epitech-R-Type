#include "WinServerSocket.hpp"

WinServerSocket::WinServerSocket(void)
{
	_socket = 0;
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
	_host = listenHost;
	_port = listenPort;

	SOCKADDR_IN sin;
	//char ipstr[INET6_ADDRSTRLEN];
	int ret = 0;
	u_long socket_state = 0;


	sin.sin_family = AF_INET;
	//sin.sin_addr.s_addr = inet_pton(AF_INET, _host.c_str(), ipstr);
	//sin.sin_addr.s_addr = inet_addr(_host.c_str());
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(_port);
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	char value = 1;
	setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));
	//ioctlsocket(_socket, FIONBIO, &socket_state);
	if (_socket <= 0) {
		throw (std::runtime_error("bad socket"));
	}
	ret = bind(_socket, reinterpret_cast<SOCKADDR *>(&sin), sizeof(sin));
	if (ret < 0) {
		closesocket(_socket);
		_socket = 0;
		throw (std::runtime_error("error on bind"));
	}
	ret = listen(_socket, SOMAXCONN);
	if (ret < 0) {
		closesocket(_socket);
		_socket = 0;
		throw (std::runtime_error("error on listen"));
	}
}

std::shared_ptr<ITCPSocket> WinServerSocket::accept(void)
{
	std::shared_ptr<ITCPSocket> socket = std::make_shared<TCPWinSocket>();
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
