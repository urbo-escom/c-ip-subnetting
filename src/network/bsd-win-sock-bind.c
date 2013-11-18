#include <stdlib.h>
#include "bsd-win-sock.h"
#include "bsd-win-sock-types.h"
#include "debug.h"

#define T Socket_T

extern int Socket_bind(T* sock) {
	log_debug("Obtaining socket");
	sock->sockfd_src = socket(sock->result->ai_family,
	                          sock->result->ai_socktype,
	                          sock->result->ai_protocol);

	if (sock->sockfd_src == INVALID_SOCKET) {
		Socket_set_errno(SOCKET_ERR_SOCKET);
		log_err("Got an invalid socket: %s",
		         Socket_strerror());
		return -1;
	}

#ifdef __linux
	int yes = 1;
	#define value() (&yes)
#elif _WIN32
	BOOL yes = 1;
	#define value() ((const char *)&yes)
#endif
	log_debug("Setting socket for reuse address");
	if (setsockopt(sock->sockfd_src, SOL_SOCKET, SO_REUSEADDR,
	               value(), sizeof(yes)) == SOCKET_ERROR) {
		Socket_set_errno(SOCKET_ERR_SET_SOCK_OPT);
		log_warn("Can't reuse address: %s", Socket_strerror());
	}

	log_debug("Binding socket");
	int value = bind(sock->sockfd_src, sock->result->ai_addr,
	                 (socklen_t)(sock->result->ai_addrlen));

	if (value == SOCKET_ERROR) {
		Socket_set_errno(SOCKET_ERR_BIND);
		log_err("Bind failed: %s",
		         Socket_strerror());
		return -1;
	}

	log_debug("Socket bind succeded");
	return value;
}

