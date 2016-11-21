#include <thread>
#include <iostream>
#include "WinSocket.h"
#include "WinServerSocket.h"

void ThreadFunc() {
	ISocket* sockc = NULL;
#ifdef WIN32
	IServerSocket* sock = new WinServerSocket();
#else

#endif // WIN32
	sock->init("0.0.0.0", 4242);
	while ((sockc = sock->accept())) {
		sockc->send("TEST\r\n");
		delete sockc;
	}
}


int main() {
	std::thread th(ThreadFunc);

#ifdef WIN32
	ISocket* sock = new WinSocket();
#else

#endif // WIN32
	sock->connectToServer("127.0.0.1", 4242);
	std::cout << sock->recv();

	th.join();

	return 0;
}

