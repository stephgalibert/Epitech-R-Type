//
// Application.cpp for  in /home/jordan/workspace/R-type/server
//
// Made by jordan
// Login   <jordan@epitech.net>
//
// Started on  Mon Nov 21 16:30:56 2016 jordan
// Last update Mon Nov 21 16:43:05 2016 jordan
//

#include "Application.hpp"

Application::Application(void)
{
	
}

Application::~Application(void)
{
	for (auto it : _servers) {
		it->close();
		delete (it);
	}
}

void Application::init(void)
{
	StaticTools::Log.open("server.log", std::ios::app | std::ios::out);

	// create UDP and TCP server
	TCPServer *tcp = new TCPServer(_pm);
	try {
		tcp->init();
	}
	catch (std::exception const& e) {
		delete (tcp);
		throw (std::runtime_error(e.what()));
	}

	_servers.push_back(tcp);
}

void Application::run(void)
{
	for (auto it : _servers) {
		it->open();
	}
}
