#pragma once

#include <memory>

#include "ITCPSocket.hpp"

class IServerSocket : public std::enable_shared_from_this<IServerSocket>
{
public:
	virtual ~IServerSocket(void) {}

	virtual void init(std::string const& listenHost, short listenPort) = 0;
	virtual std::shared_ptr<ITCPSocket> accept(void) = 0;
};
