#include <stdlib.h>
#include "bsd-win-sock.h"
#include "bsd-win-sock-types.h"
#include "debug.h"

#define T Socket_T

extern int Socket_receive(T* sock, char* msg, int msg_len) {
	msg[0] = '\0';
	int n = recv(sock->sockfd_dest, msg, msg_len, 0);

	if (n == SOCKET_ERROR) {
		Socket_set_errno(SOCKET_ERR_RECV);
		log_err("Receive failed: %s", Socket_strerror());
		return -1;
	}

	log_debug("NULL terminating message");
	msg[n] = '\0';

	log_debug("Message: '%s'", msg);
	return n;
}

