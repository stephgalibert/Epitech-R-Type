#include <iostream>

#include "StaticTools.hpp"
#include "Application.hpp"

int main(void)
{
	Application app;
	
	try {
		app.init();
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
	}

	app.run();

	while (true); // manage input ?

	return (0);
}
