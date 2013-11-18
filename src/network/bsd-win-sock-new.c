#include <stdlib.h>
#include "bsd-win-sock.h"
#include "bsd-win-sock-types.h"
#include "bsd-win-setup.h"
#include "debug.h"

#define T Socket_T

extern T* Socket_new(const char* address, const char* portnum) {
	log_debug("Creating new socket");
	if (Socket_startup() < 0)
		return NULL;

	log_debug("Mallocing Socket_T");
	T* sock = (T*)malloc(sizeof(T));

	if (sock == NULL) {
		Socket_set_errno(SOCKET_ERR_MEMORY);
		log_err("Malloc failed");
		return NULL;
	}

	log_debug("Initializing Socket_T: %s:%s",
	         address != NULL?address:"ANY", portnum);
	sock->sockfd_src = INVALID_SOCKET;
	sock->sockfd_dest = INVALID_SOCKET;
	sock->result = NULL;
	sock->peer_ip[0] = '\0';
	sock->peer_port[0] = '\0';
	sock->address = address;
	sock->portnum = portnum;

	Socket_set_hints(sock);
	log_debug("Getting addrinfo");
	if (getaddrinfo(sock->address, sock->portnum,
	                &(sock->hints), &(sock->result)) != 0) {
		Socket_set_errno(SOCKET_ERR_GETADDRINFO);
		log_err("Getaddrinfo failed: %s", Socket_strerror());
		Socket_free(&sock);
		log_err("Socket creation failed");
		return NULL;
	}

	log_debug("Socket creation succeded");
	return sock;
}

#undef T

