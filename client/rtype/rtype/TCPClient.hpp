#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <queue>
#include <fstream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include "IClient.hpp"
#include "StaticTools.hpp"
#include "RequestHandler.hpp"

class TCPClient : public IClient
{
public:
	TCPClient(std::string const& remote, std::string const& port);
	virtual ~TCPClient(void);

	virtual void connect(void);
	virtual void write(ICommand *packet);
	virtual void disconnect(void);
	virtual void run(void);
	virtual bool isConnected(void) const;
	virtual IClient &operator<<(ICommand *packet);

private:
	void read(void);
	void write(void);

	void do_connect(boost::system::error_code const& ec, boost::asio::ip::tcp::resolver::iterator);
	void do_read(boost::system::error_code const& ec, size_t);
	void do_write(boost::system::error_code const& ec, size_t);

	void runThread(void);

	boost::asio::io_service _io_service;
	boost::asio::deadline_timer _timer;
	boost::asio::ip::tcp::resolver _resolver;
	boost::asio::ip::tcp::socket _socket;

	boost::asio::streambuf _read;
	//std::queue<char *> _toWrites;
	std::queue<ICommand *> _toWrites;

	bool _connected;
	RequestHandler _reqHandler;

	std::thread _runThread;

	std::string _remote;
	std::string _port;
};

