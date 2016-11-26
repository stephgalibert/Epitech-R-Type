#include <iostream>

#include "Application.hpp"

int main(int ac, char **av)
{
	Application app;
	
	try {
		app.init();
	}
	catch (std::exception const& e) {
		std::cerr << e.what() << std::endl;
	}

	app.run();

	return (0);
}