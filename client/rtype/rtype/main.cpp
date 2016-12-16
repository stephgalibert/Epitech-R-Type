#include "Application.hpp"

#ifdef WIN32
# include <Windows.h>
#endif

int main(int ac, char **av)
{
//#ifdef WIN32
//	FreeConsole();
//#endif

	std::string host;
	std::string pwd;

	if (ac > 1) {
		host = av[1];
		pwd = av[2];
	}

	Application app;

	try {
		app.init(host, pwd);
	}
	catch (std::exception const& e) {
		std::cerr << "main: " << e.what() << std::endl;
		return (42);
	}

	app.loop();

	return (0);
}