#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

#include <boost/noncopyable.hpp>

#include "Protocol.hpp"
#include "IRequest.hpp"

class RequestBuilder : private boost::noncopyable
{
public:
	typedef std::function<std::unique_ptr<IRequest>(void)> Cmds;
public:
	RequestBuilder(void);
	~RequestBuilder(void);

	std::unique_ptr<IRequest> create(CommandType type) const;
private:
	//std::unique_ptr<IRequest> kill(void) const;

	std::unordered_map<int, Cmds> _cmds;
};
