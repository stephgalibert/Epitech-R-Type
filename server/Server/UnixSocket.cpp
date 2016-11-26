#include "UnixSocket.hpp"

UnixSocket::UnixSocket(SocketType type)
{
	_type = type;
	_socket = 0;
}

UnixSocket::~UnixSocket(void)
{
	if (_socket)
		closesocket(_socket);
}

bool UnixSocket::connectToServer(std::string const & host, short port)
{
	SOCKADDR_IN sin;
	int ret = 0;
	_socket = socket(AF_INET, _type, 0);
	if (_socket <= 0) {
		return false;
	}
	sin.sin_addr.s_addr = inet_addr(host.c_str());
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	if (connect(_socket, reinterpret_cast<SOCKADDR *>(&sin), sizeof(sin))) {
		closesocket(_socket);
		return false;
	}
	return true;
}

bool UnixSocket::connectFromAcceptedFd(int fd)
{
	_socket = fd;
	return true;
}

int UnixSocket::recv(std::string & buffer, int blocksize)
{
	char *buf = new char[blocksize] {0};
	int ret = 0;

	ret = ::recv(_socket, buf, blocksize * sizeof(char), 0);
	buffer = std::string(buf);

	delete buf;
	return ret;
}

std::string UnixSocket::recv(void)
{
	std::string ret;
	std::string buf;

	while (recv(buf, 4096) == 4096) {
		ret += buf;
	}
	ret += buf;
	return ret;
}

int UnixSocket::send(std::string const & data)
{
	return ::send(_socket, data.c_str(), data.length() + 1, 0);
}
