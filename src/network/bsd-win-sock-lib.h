#ifndef BSD_WIN_SOCK_LIB_H_INCLUDED
#define BSD_WIN_SOCK_LIB_H_INCLUDED

#ifdef __linux
	#include <unistd.h>
	#include <netdb.h>
	#include <sys/types.h>
	#include <netinet/in.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1
#elif _WIN32
	/* Comes in the example of MSDN simple server */
	#undef UNICODE
	/* Comes in the example of MSDN simple server */
	#define WIN32_LEAN_AND_MEAN
	/* getaddrinfo and freeaddrinfo doesn't work without this */
	#undef _WIN32_WINNT
	#define _WIN32_WINNT 0x501
	/* Comes in the example of MSDN simple client */
	#include <windows.h>
	#include <winsock2.h>
	#include <ws2tcpip.h>
	/* MSDN says socket isn't a file descriptor */
	#define close(s) do{\
			closesocket((s));\
			WSACleanup();\
		} while(0)
	#define socklen_t int
#endif

#endif

