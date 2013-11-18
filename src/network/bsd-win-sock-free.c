#include <stdlib.h>
#include "bsd-win-sock.h"
#include "bsd-win-sock-types.h"
#include "bsd-win-setup.h"
#include "debug.h"

#define T Socket_T

extern void Socket_free(T** sock) {
	log_debug("Freeing socket");
	if ((*sock)->sockfd_src != INVALID_SOCKET) {
		log_debug("Closing Socket fd src");
		close((*sock)->sockfd_src);
		(*sock)->sockfd_src = INVALID_SOCKET;
	}

	if ((*sock)->sockfd_dest != INVALID_SOCKET) {
		log_debug("Closing Socket fd dest");
		close((*sock)->sockfd_dest);
		(*sock)->sockfd_dest = INVALID_SOCKET;
	}

	if ((*sock)->result != NULL) {
		log_debug("Freeing result");
		freeaddrinfo((*sock)->result);
		(*sock)->result = NULL;
	}

	log_debug("Freeing and nulling Socket_T pointer");
	free(*sock);
	*sock = NULL;
}

#undef T

