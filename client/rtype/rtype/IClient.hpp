#pragma once

#include <string>

#include "Protocol.hpp"

class IClient
{
public:
	virtual ~IClient(void) {}

	virtual void connect(void) = 0;
	virtual void write(Packet *packet) = 0;
	virtual void disconnect(void) = 0;
	virtual void run(void) = 0;
	virtual bool isConnected(void) const = 0;
	virtual IClient &operator<<(Packet *packet) = 0;
	virtual Packet *createPacket(PacketType type, std::string const& data) = 0;
};