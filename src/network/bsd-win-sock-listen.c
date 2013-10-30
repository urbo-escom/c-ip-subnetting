#include <stdlib.h>
#include "bsd-win-sock.h"
#include "bsd-win-sock-types.h"
#include "debug.h"

#define T Socket_T

extern int Socket_listen(T* sock, int connections) {
	log_debug("Trying to listen to %d connections", connections);
	if (listen(sock->sockfd_src, connections) == SOCKET_ERROR) {
		Socket_set_errno(SOCKET_ERR_LISTEN);
		log_debug("Listen failed: %s", Socket_strerror());
		return -1;
	}

	log_debug("Listen succeded");
	return 0;
}

