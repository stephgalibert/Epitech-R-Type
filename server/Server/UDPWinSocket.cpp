#include "UDPWinSocket.hpp"

UDPWinSocket::UDPWinSocket()
{
	_socket = 0;
	WSAStartup(MAKEWORD(2, 0), &_wsdata);
}

UDPWinSocket::~UDPWinSocket(void)
{
	if (_socket) {
		closesocket(_socket);
	}
	WSACleanup();
}

void UDPWinSocket::init(std::string const& host)
{
	SOCKADDR_IN sin;

	if ((_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
		throw (std::runtime_error("Can't create UDP Socket : " + std::to_string(WSAGetLastError())));
	}
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(host.c_str());
	sin.sin_port = htons(4242);
	if (bind(_socket, (struct sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR) {
		throw(std::runtime_error("Bind failed with error code : " + std::to_string(WSAGetLastError())));
	}
}

void UDPWinSocket::recvFrom(Buffer &buffer, Endpoint &endpoint)
{
	int len = sizeof(endpoint.in);
	int ret = 0;

	if ((ret = ::recvfrom(_socket, buffer.getData(), buffer.getSize(), 0, (struct sockaddr *) &endpoint.in, &len)) == SOCKET_ERROR) {
		throw(std::runtime_error("recvfrom() failed with error code : " + std::to_string(WSAGetLastError())));
	}
	buffer.setSize(ret);
}

void UDPWinSocket::sendTo(char *tosend, size_t len, Endpoint const& endpoint)
{
	int slen = sizeof(endpoint.in);

	if (::sendto(_socket, tosend, len, 0, (struct sockaddr*) &endpoint.in, slen) == SOCKET_ERROR) {
		throw(std::runtime_error("sendTo() failed with error code : " + std::to_string(WSAGetLastError())));
	}
}