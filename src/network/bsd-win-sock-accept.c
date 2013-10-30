#include <stdlib.h>
#include "bsd-win-sock.h"
#include "bsd-win-sock-types.h"
#include "bsd-win-setup.h"
#include "debug.h"

#define T Socket_T

extern int Socket_accept(T* sock) {
	if (sock->sockfd_dest != INVALID_SOCKET) {
		log_debug("Closing socket: %d", sock->sockfd_dest);
		close(sock->sockfd_dest);
		sock->sockfd_dest = INVALID_SOCKET;
	}

	log_debug("Socket startup for accept");
	if (Socket_startup() < 0)
		return -1;

	log_debug("Accepting socket");
	sock->sockfd_dest = accept(sock->sockfd_src, NULL, NULL);
	if (sock->sockfd_dest == INVALID_SOCKET) {
		Socket_set_errno(SOCKET_ERR_ACCEPT);
		log_err("Accept failed: %s", Socket_strerror());
		return -1;
	}

	log_debug("Socket accepted: %d", sock->sockfd_dest);
	return 0;
}

