#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <unordered_map>
#include <sstream>
#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/algorithm/string.hpp>

#include "IClient.hpp"
#include "RequestBuilder.hpp"
#include "Protocol.hpp"
#include "StaticTools.hpp"

#include "IRequest.hpp"

class TCPClient;

class RequestHandler : private boost::noncopyable
{
public:
	RequestHandler(void);
	~RequestHandler(void);

	void receive(IClient &client, std::shared_ptr<ICommand> received,
				 std::shared_ptr<ICommand> &toSend);

 private:
	//RequestBuilder _builder;
};
