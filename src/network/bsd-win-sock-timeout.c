#include <stdlib.h>
#include "bsd-win-sock.h"
#include "bsd-win-sock-types.h"
#include "debug.h"

#define T Socket_T

extern int Socket_timeout(T* sock, int seconds) {
	log_debug("Setting timeout");
#ifdef __linux
	#define my_timeout_t char *
	struct timeval timeout;
		timeout.tv_sec = seconds;
		timeout.tv_usec = 0;
#elif _WIN32
	#define my_timeout_t const char *
	DWORD timeout = seconds*1000;
#endif

        if(setsockopt(sock->sockfd_dest, SOL_SOCKET, SO_RCVTIMEO,
	           (my_timeout_t)&timeout,
	           sizeof(timeout)) == SOCKET_ERROR) {
		Socket_set_errno(SOCKET_ERR_SET_SOCK_OPT);
		log_warn("Timeout set failed: %s", Socket_strerror());
		return -1;
	}

	return 0;
}

