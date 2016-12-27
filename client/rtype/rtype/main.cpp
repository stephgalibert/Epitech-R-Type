#include "Application.hpp"
#include "XMLReader.hpp"
#include "StaticTools.hpp"

#ifdef WIN32
# include <Windows.h>
#endif

int main(int ac, char **av)
{
//#ifdef WIN32
//	FreeConsole();
//#endif
	StaticTools::Log.open("client.log", std::ios::out | std::ios::app);

	XMLReader config;
	std::string ip, port;
	std::string username, host, pwd;
	if (ac > 2) {
		if (std::string(av[1]).compare("rtype:")) {
			username = av[1];
			host = av[2];
			pwd = av[3];
		} else {
			username = av[2];
			host = av[3];
			pwd = av[4];
		}
	}
	else { // TEST:
		username = "test";
		host = "host";
		pwd = "pwd";
	}

	try {
		config.readFromFile("config.xml");
		ip = config.getValue<std::string>("config", "ip");
		port = config.getValue<std::string>("config", "port");
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
		return (42);
	}

	std::cout << username << ":" << ip << ":" << port << std::endl;

	Application app(ip, port);

	try {
		app.init(username, host, pwd);
	}
	catch (std::exception const& e) {
		std::cerr << "main: " << e.what() << std::endl;
		return (42);
	}

	app.loop();

	return (0);
}