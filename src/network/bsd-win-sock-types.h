#ifndef BSD_WIN_SOCK_TYPES_H_INCLUDED
#define BSD_WIN_SOCK_TYPES_H_INCLUDED

#define SOCKET_ERR_MEMORY -3
#define SOCKET_ERR_GETADDRINFO -4
#define SOCKET_ERR_SOCKET -5
#define SOCKET_ERR_SERVER_UNAVAILABLE -6
#define SOCKET_ERR_BIND -7
#define SOCKET_ERR_LISTEN -8
#define SOCKET_ERR_ACCEPT -9
#define SOCKET_ERR_CONNECT -10
#define SOCKET_ERR_SEND -11
#define SOCKET_ERR_RECV -12
#define SOCKET_ERR_WSA_STARTUP -13
#define SOCKET_ERR_WSA_SHUTDOWN -14
#define SOCKET_ERR_SET_SOCK_OPT -15
#define SOCKET_ERR_GET_PEER_NAME -16

#include "bsd-win-sock-lib.h"

struct Socket_T {
	int sockfd_dest; /* end point */
	int sockfd_src;  /* self */
	struct addrinfo hints;
	struct addrinfo *result;

	char peer_ip[20];
	char peer_port[20];

	const char* address;
	const char* portnum;
};

#endif

