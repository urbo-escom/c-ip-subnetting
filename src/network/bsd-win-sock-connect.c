#include <stdlib.h>
#include "bsd-win-sock.h"
#include "bsd-win-sock-types.h"
#include "debug.h"

#define T Socket_T

extern int Socket_connect(T* sock) {
	struct addrinfo *ptr;
	log_debug("Searching available addrinfos");
	for(ptr = sock->result; ptr != NULL; ptr = ptr->ai_next) {
		log_debug("Obtaining socket");
		sock->sockfd_dest = socket(
			ptr->ai_family,
			ptr->ai_socktype,
			ptr->ai_protocol);
		if (sock->sockfd_dest == INVALID_SOCKET) {
			Socket_set_errno(SOCKET_ERR_SOCKET);
			log_err("Invalid socket: %s", Socket_strerror());
			return sock->sockfd_dest;
		}

		if (connect(sock->sockfd_dest, ptr->ai_addr,
		           (socklen_t)ptr->ai_addrlen) == SOCKET_ERROR) {
			close(sock->sockfd_dest);
			Socket_set_errno(SOCKET_ERR_CONNECT);
			log_warn("Unable to connect: %s", Socket_strerror());
			sock->sockfd_dest = INVALID_SOCKET;
			continue;
		}
		break;
	}

	if (sock->sockfd_dest == INVALID_SOCKET) {
		Socket_set_errno(SOCKET_ERR_SERVER_UNAVAILABLE);
		log_warn("Server unavailable: %s", Socket_strerror());
		return -1;
	}

	return 0;
}

