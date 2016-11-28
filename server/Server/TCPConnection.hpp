#pragma once

#include "AConnection.hpp"

#include "ITCPSocket.hpp"

#include "ThreadPool.hpp"
#include "ReadAsyncTask.hpp"
#include "WriteAsyncTask.hpp"

class TCPConnection : public AConnection
{
public:
	static void AsyncRead(std::shared_ptr<ITCPSocket> socket, size_t transferAtLeast,
		std::function<void(char *, size_t)> callback);

	static void AsyncWrite(std::shared_ptr<ITCPSocket> socket, char *buffer, size_t size,
		std::function<void(void)> callback);

public:
	TCPConnection(std::shared_ptr<ITCPSocket> socket, ConnectionManager &cm,
		RequestHandler &rh, PartyManager &pm);
	virtual ~TCPConnection(void);

	virtual void start(void);
	virtual void close(void);

	virtual void write(ICommand *command);

private:
	void read(void);
	void write(void);

	virtual void do_read(char *data, size_t size);
	virtual void do_write(void);

	std::shared_ptr<ITCPSocket> _socket;
	std::queue<ICommand *> _toWrites;
};

