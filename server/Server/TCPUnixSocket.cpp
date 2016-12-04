#include "TCPUnixSocket.hpp"

TCPUnixSocket::TCPUnixSocket(void)
{
  _socket = 0;
}

TCPUnixSocket::~TCPUnixSocket(void)
{
  if (_socket)
    close(_socket);
}

bool TCPUnixSocket::connectToServer(std::string const & host, short port)
{
  sockaddr_in sin;
  //int ret = 0;
  _socket = socket(AF_INET, SOCK_STREAM, 0);
  if (_socket <= 0) {
    return false;
  }
  sin.sin_addr.s_addr = inet_addr(host.c_str());
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  if (connect(_socket, reinterpret_cast<sockaddr *>(&sin), sizeof(sin))) {
    close(_socket);
    return false;
  }
  return true;
}

bool TCPUnixSocket::connectFromAcceptedFd(int fd)
{
  _socket = fd;
  return true;
}

int TCPUnixSocket::recv(char *buffer, size_t blocksize)
{
  return (::recv(_socket, buffer, blocksize * sizeof(char), 0));
}

bool TCPUnixSocket::recv(Buffer &buffer, size_t transferAtLeast)
{
  char buf[1024];
  int read = 0;
  size_t total = 0;
  
  while (total < transferAtLeast && (read = recv(buf, 1024)) > 0) {
    buffer.reallocate(buf, read);
    total += read;
  }
  return (read > 0);
}

int TCPUnixSocket::send(char *data, size_t size)
{
  int read = 0;
  
  read = ::send(_socket, data, size, 0);
  //std::cout << "send " << read << " bytes" << std::endl;
  
  return (read);
}
