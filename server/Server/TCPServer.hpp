#pragma once

#include "AServer.hpp"
#include "AcceptAsyncTask.hpp"

class TCPServer : public AServer
{
public:
	static void AsyncAccept(IServerSocket *ss, std::function<void(ISocket *)> function);
public:
	TCPServer(PartyManager &pm);
	virtual ~TCPServer(void);

	virtual void init(void);
	virtual void open(void);
	virtual void close(void);

private:
	void accept(void);
	void do_accept(ISocket *socket);

	IServerSocket *_ss;
};

