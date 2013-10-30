#include <string.h>
#include "bsd-win-sock.h"
#include "bsd-win-sock-types.h"
#include "bsd-win-setup.h"
#include "debug.h"

extern int Socket_set_hints(Socket_T* sock) {
	log_debug("Zeroing the sock->hints");
	memset(&(sock->hints), 0, sizeof(sock->hints));

	log_debug("Setting socktype and protocol");
	sock->hints.ai_socktype = SOCK_STREAM;
	sock->hints.ai_protocol = IPPROTO_TCP;

	if (sock->address == NULL) { /* <-- The Server */
		log_debug("Setting up server socket");
		sock->hints.ai_family = AF_INET;
		sock->hints.ai_flags = AI_PASSIVE;
	} else { /* <-- Not the Server */
		log_debug("Setting up client socket");
		sock->hints.ai_family = AF_UNSPEC;
	}

	return 0;
}

