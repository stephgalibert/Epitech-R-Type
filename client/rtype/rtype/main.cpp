#include "Application.hpp"

//#include <bitset>

//void test(void)
//{
//	uint8_t direction = 0;
//
//	direction |= E;
//	//direction |= N;
//
//	std::cout << "direction: " << std::bitset<8>(direction) << std::endl;
//
//	if (direction & E && direction & N) {
//		std::cout << "true" << std::endl;
//	}
//}

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
		std::cerr << e.what() << std::endl;
		return (42);
	}

	app.loop();

	return (0);
}