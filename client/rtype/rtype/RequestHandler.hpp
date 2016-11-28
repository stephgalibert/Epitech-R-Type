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
//#include "RequestBuilder.h"
#include "Protocol.hpp"
#include "StaticTools.hpp"

class TCPClient;

class RequestHandler : private boost::noncopyable
{
public:
	RequestHandler(void);
	~RequestHandler(void);

	void request(IClient &client, char const *received, ICommand **toSend);

 private:
	//RequestBuilder _builder;
};
