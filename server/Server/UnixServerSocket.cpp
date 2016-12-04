#include "UnixServerSocket.hpp"
#include "TCPUnixSocket.hpp"

UnixServerSocket::UnixServerSocket(void)
{
	_socket = 0;
}


UnixServerSocket::~UnixServerSocket(void)
{
	if (_socket < 1)
		close(_socket);
}

void UnixServerSocket::init(std::string const & listenHost, short listenPort)
{
	sockaddr_in sin;
	int ret = 0;

	sin.sin_addr.s_addr = inet_addr(listenHost.c_str());
	sin.sin_family = AF_INET;
	sin.sin_port = htons(listenPort);
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket <= 0) {
		throw (std::runtime_error("bad socket"));
	}
	ret = bind(_socket, reinterpret_cast<sockaddr *>(&sin), sizeof(sin));
	if (ret < 0) {
	  close(_socket);
		_socket = 0;
	}
	ret = listen(_socket, 0);
	if (ret < 0) {
		close(_socket);
		_socket = 0;
	}
}

std::shared_ptr<ITCPSocket> UnixServerSocket::accept(void)
{
	std::shared_ptr<ITCPSocket> socket = std::make_shared<TCPUnixSocket>();
	//ISocket *socket = new UnixSocket(_type);
        sockaddr_in csin;
	int csock;
	socklen_t sinsize;

	sinsize = sizeof(csin);
	if ((csock = ::accept(_socket, (sockaddr *)&csin, &sinsize))) {
		socket->connectFromAcceptedFd(csock);
		return (socket);
	}
	return (NULL);
}
