#pragma once

#include <iostream>
#include <memory>
#include <queue>
#include <functional>

#include "ISocket.hpp"
#include "RequestHandler.hpp"
#include "ICommand.hpp"

#include "ThreadPool.hpp"
#include "ReadAsyncTask.hpp"
#include "WriteAsyncTask.hpp"

#include "StaticTools.hpp"
#include "ConnectionManager.hpp"

class Party;
class PartyManager;

class AConnection : public std::enable_shared_from_this<AConnection>
{
public:
	static void AsyncRead(std::shared_ptr<ISocket> socket, size_t transferAtLeast,
							std::function<void(char *, size_t)> callback);

	static void AsyncWrite(std::shared_ptr<ISocket> socket, Buffer &buffer,
							std::function<void(void)> callback);

public:
	AConnection(std::shared_ptr<ISocket> socket, ConnectionManager &cm,
					RequestHandler &rh, PartyManager &pm);
	~AConnection(void);

	void start(void);
	void close(void);

	void write(ICommand *command);

	PartyManager const& getPartyManager(void) const;
	RequestHandler const& getRequestHandler(void) const;

	std::shared_ptr<Party> getCurrentParty(void) const;
	void setID(int id);

private:
	void read(void);
	void do_read(char *data, size_t size);

	void write(void);
	void do_write(void);

	PartyManager &_pm;
	RequestHandler &_rh;
	ConnectionManager &_cm;

	std::shared_ptr<ISocket> _socket;
	std::queue<ICommand *> _toWrites;
	bool _running;

	//std::shared_ptr<Party> _party;
	int _id;
	bool _ready;
};

