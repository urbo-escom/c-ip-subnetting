#include <stdlib.h>
#include "bsd-win-sock.h"
#include "bsd-win-sock-types.h"
#include "debug.h"

#define T Socket_T

/* Stol... I mean adapted from Beej's Guide:
http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html#sendall */
extern int Socket_send(T* sock, const char* msg, int len) {
	int total = 0;
	int bytesleft = len;
	int n;

	log_debug("Sending %d chars, message: %.*s", len, len, msg);
	while (total < len) {
		n = send(sock->sockfd_dest, msg + total, bytesleft, 0); 
		if (n == -1)
			break;
		total += n;
		bytesleft -= n;
		log_debug("---send: %d/%d", total, len);
		log_debug("---bytes left: %d", bytesleft);
		log_debug("---message left: %.*s", bytesleft, msg + total);
	}

	if (n == SOCKET_ERROR) {
		Socket_set_errno(SOCKET_ERR_SEND);
		log_warn("Send failed: %s", Socket_strerror());
		return -1;
	}

	log_debug("Send succeded");
	return total;
}

