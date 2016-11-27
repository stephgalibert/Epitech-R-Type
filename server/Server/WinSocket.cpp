#include "WinSocket.hpp"

WinSocket::WinSocket(SocketType type)
{
	_socket = 0;
	_type = type;
	WSAStartup(MAKEWORD(2, 0), &_wsdata);
}

WinSocket::~WinSocket(void)
{
	if (_socket) {
		closesocket(_socket);
	}
	WSACleanup();
}

bool WinSocket::connectToServer(std::string const& host, short port)
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

bool WinSocket::connectFromAcceptedFd(int fd)
{
	_socket = fd;
	return true;
}

int WinSocket::recv(char *buffer, size_t blocksize)
{
	return (::recv(_socket, buffer, blocksize * sizeof(char), 0));
}

void WinSocket::recv(Buffer &buffer, size_t transferAtLeast)
{
	char buf[1024];
	int read = 0;
	size_t total = 0;

	while (total < transferAtLeast && (read = recv(buf, 1024)) > 0) {
		buffer.reallocate(buf, read);
		total += read;
	}
}

int WinSocket::send(char *data, size_t size)
{
	return ::send(_socket, data, size, 0);
}
