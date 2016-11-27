#pragma once

#include "AServer.hpp"
#include "AcceptAsyncTask.hpp"

#include "AConnection.hpp"

class TCPServer : public AServer
{
public:
	static void AsyncAccept(std::shared_ptr<IServerSocket> ss,
		                    std::function<void(std::shared_ptr<ISocket>)> function);

public:
	TCPServer(ConnectionManager &cm, PartyManager &pm);
	virtual ~TCPServer(void);

	virtual void init(void);
	virtual void open(void);
	virtual void close(void);

private:
	void accept(void);
	void do_accept(std::shared_ptr<ISocket> socket);

	std::shared_ptr<IServerSocket> _ss;
};

