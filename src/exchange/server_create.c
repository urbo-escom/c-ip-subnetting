#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bsd-win-sock.h"
#include "exchange.h"
#include "debug.h"

extern Server_T* Server_create(char* port) {
	Server_T* sock = (Server_T*)Socket_new(NULL, port);

	if (sock == NULL) {
		log_err("Server creation failed: %s", Socket_strerror());
		return NULL;
	}

	if (Socket_bind(sock) < 0) {
		log_err("Server binding failed %s", Socket_strerror());
		Socket_free(&sock);
		return NULL;
	}

	if (Socket_listen(sock, 1) < 0) {
		log_err("Server listening failed %s", Socket_strerror());
		Socket_free(&sock);
		return NULL;
	}

	return sock;
}

extern void Server_close(Server_T** sock) {
	Socket_free(sock);
}

