#pragma once

#include "AServer.hpp"
#include "AcceptAsyncTask.hpp"

#include "AConnection.hpp"
#include "ITCPSocket.hpp"
#include "TCPConnection.hpp"

#ifdef _WIN32
# include "WinServerSocket.hpp"
#else 
# include "UnixServerSocket.hpp"
#endif

class TCPServer : public AServer
{
public:
	static void AsyncAccept(std::shared_ptr<IServerSocket> ss,
		                    std::function<void(std::shared_ptr<ITCPSocket>)> function);

public:
	TCPServer(ConnectionManager &cm, PartyManager &pm);
	virtual ~TCPServer(void);

	virtual void init(void);
	virtual void open(void);
	virtual void close(void);

private:
	void accept(void);
	void do_accept(std::shared_ptr<ITCPSocket> socket);

	std::shared_ptr<IServerSocket> _ss;
};

