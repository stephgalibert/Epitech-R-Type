#pragma once

#ifdef _WIN32
# include <winsock2.h>
#else
# include <netinet/in.h>
#endif

struct Endpoint
{
	sockaddr_in in;
};