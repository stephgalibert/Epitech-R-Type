#pragma once

#include <mutex>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "ITCPSocket.hpp"
#include "Buffer.hpp"

class TCPUnixSocket : public ITCPSocket
{
public:

public:
  TCPUnixSocket(void);
  virtual ~TCPUnixSocket(void);
  
  virtual bool connectToServer(std::string const& host, short port);
  virtual bool connectFromAcceptedFd(int fd);
  virtual int recv(char *buffer, size_t blocksize);
  virtual bool recv(Buffer &buffer, size_t transferAtLeast);
  virtual int send(char *data, size_t size);
  
private:
  int _socket;
  std::mutex _mutex;
};
