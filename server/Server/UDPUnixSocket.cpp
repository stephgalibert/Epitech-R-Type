#include "UDPUnixSocket.hpp"

UDPUnixSocket::UDPUnixSocket(void)
{
	_socket = 0;
}

UDPUnixSocket::~UDPUnixSocket(void)
{
}

void UDPUnixSocket::init(std::string const& host)
{
	sockaddr_in sin;
	
	if ((_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
		throw (std::runtime_error("Can't create UDP Socket : "));
	}
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(host.c_str());
	sin.sin_port = htons(4242);
	if (bind(_socket, (struct sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR) {
		throw(std::runtime_error("Bind failed with error code : "));
	}
}

void UDPUnixSocket::recvFrom(Buffer &buffer, Endpoint &endpoint)
{
	int len = sizeof(endpoint.in);
	int ret = 0;

	if ((ret = ::recvfrom(_socket, buffer.getData(), buffer.getSize(), 0, (struct sockaddr *) &endpoint.in, &len)) == SOCKET_ERROR) {
		throw(std::runtime_error("recvfrom() failed with error code : "));
	}
	buffer.setSize(ret);
}

void UDPUnixSocket::sendTo(char *tosend, size_t len, Endpoint const& endpoint)
{
	int slen = sizeof(endpoint.in);

	if (::sendto(_socket, tosend, len, 0, (struct sockaddr*) &endpoint.in, slen) == SOCKET_ERROR) {
		throw(std::runtime_error("sendTo() failed with error code : "));
	}
}