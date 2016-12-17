#include "TCPWinSocket.hpp"

TCPWinSocket::TCPWinSocket(void)
{
	_socket = 0;
	WSAStartup(MAKEWORD(2, 0), &_wsdata);
}

TCPWinSocket::~TCPWinSocket(void)
{
	if (_socket) {
		closesocket(_socket);
	}
	WSACleanup();
}

//bool TCPWinSocket::connectToServer(std::string const& host, short port)
//{
//	SOCKADDR_IN sin;
//	char ipstr[INET6_ADDRSTRLEN];
//	int ret = 0;
//	_socket = socket(AF_INET, SOCK_STREAM, 0);
//	if (_socket <= 0) {
//		return false;
//	}
//	sin.sin_family = AF_INET;
//	sin.sin_addr.s_addr = inet_pton(AF_INET, host.c_str(), ipstr);
//	//sin.sin_addr.s_addr = inet_addr(host.c_str());
//	sin.sin_port = htons(port);
//	if (connect(_socket, reinterpret_cast<SOCKADDR *>(&sin), sizeof(sin))) {
//		closesocket(_socket);
//		return false;
//	}
//	return true;
//}

bool TCPWinSocket::connectFromAcceptedFd(int fd)
{
	_socket = fd;
	return true;
}

int TCPWinSocket::recv(char *buffer, size_t blocksize)
{
	return (::recv(_socket, buffer, blocksize * sizeof(char), 0));
}

bool TCPWinSocket::recv(Buffer &buffer, size_t transferAtLeast)
{
	char buf[1024];
	int read = 0;
	size_t total = 0;

	std::cout << "in recv" << std::endl;
	while (total < transferAtLeast && (read = recv(buf, 1024)) > 0) {
		buffer.reallocate(buf, read);
		total += read;
	}
	return (read > 0);
}

int TCPWinSocket::send(char *data, size_t size)
{
	int read = 0;

	read = ::send(_socket, data, size, 0);
	//std::cout << "send " << read << " bytes" << std::endl;

	return (read);
}
