
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "IServerSocket.hpp"

class UnixServerSocket : public IServerSocket
{
public:
  UnixServerSocket(void);
  virtual ~UnixServerSocket(void);
  
  virtual void init(std::string const &listenHost, short listenPort);
  virtual std::shared_ptr<ITCPSocket> accept(void);
  
private:
  int _socket;
  std::string _host;
  short _port;
};

