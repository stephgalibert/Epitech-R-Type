#include "Application.hpp"

int main(int ac, char **av)
{
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
		std::cerr << e.what() << std::endl;
		return (42);
	}

	app.loop();

	return (0);
}