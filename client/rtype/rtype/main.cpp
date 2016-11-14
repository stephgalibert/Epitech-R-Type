#include <SFML/Graphics.hpp>

#include "Application.hpp"

int main(void)
{
	Application app;

	try {
		app.init();
	}
	catch (std::exception const& e) {
		std::cerr << e.what() << std::endl;
		return (42);
	}

	app.loop();

	return (0);
}