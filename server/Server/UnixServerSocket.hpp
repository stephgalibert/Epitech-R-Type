
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "IServerSocket.hpp"
#include "SocketType.hpp"

class UnixServerSocket : public IServerSocket
{
public:
	UnixServerSocket(SocketType type);
	virtual ~UnixServerSocket(void);

	virtual void init(std::string const &listenHost, short listenPort);
	virtual std::shared_ptr<ISocket> accept(void);

private:
	int _socket;
	SocketType _type;
};

