#pragma once

#include <memory>

#include "AServer.hpp"

#include "StaticTools.hpp"
#include "UDPConnection.hpp"

class UDPServer : public AServer
{
public:
	UDPServer(ConnectionManager &cm, PartyManager &pm);
	virtual ~UDPServer(void);

	virtual void init(void);
	virtual void open(void);
	virtual void close(void);

private:
	std::shared_ptr<UDPConnection> _connection;
};

