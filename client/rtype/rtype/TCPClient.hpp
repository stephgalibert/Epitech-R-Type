#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <queue>
#include <fstream>
#include <mutex>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include "IClient.hpp"
#include "StaticTools.hpp"
#include "RequestHandler.hpp"

class TCPClient : public IClient
{
public:
	TCPClient(GameController **game, MainMenuController &menu,
				std::string const& remote, std::string const& port);
	virtual ~TCPClient(void);

	virtual void connect(void);
	virtual void write(std::shared_ptr<ICommand> packet);
	virtual void disconnect(void);
	virtual void run(void);
	virtual void setRemote(std::string const& ip, std::string const& port);
	virtual bool isConnected(void) const;
	//virtual void setGameController(GameController *controller);
	virtual GameController *getGameController(void) const;
	virtual MainMenuController &getMainMenuController(void);
	virtual IClient &operator<<(std::shared_ptr<ICommand> packet);

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
	std::queue<std::shared_ptr<ICommand> > _toWrites;
	bool _connected;
	RequestHandler _reqHandler;
	GameController **_game;
	MainMenuController &_menu;

	std::thread _runThread;

	std::string _remote;
	std::string _port;
	std::mutex _mutex;
};

