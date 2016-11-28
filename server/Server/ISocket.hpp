#pragma once

#include <string>
#include <iostream>
#include <memory>

#include "Buffer.hpp"

class ISocket : public std::enable_shared_from_this<ISocket>
{
public:
	virtual ~ISocket(void) {}
};
