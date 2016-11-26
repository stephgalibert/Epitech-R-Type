#pragma once

#include <stdint.h>

#ifdef _WIN32
# include <winsock2.h>
#else
# include <sys/socket.h>
#endif

enum SocketType
{
	TCP = SOCK_STREAM,
	UDP = SOCK_DGRAM
};