#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

#include "bsd-win-sock.h"
#include "exchange.h"
#include "debug.h"

extern Client_T* Client_create(const char* ip, const char* port) {
	Client_T* sock = (Client_T*)Socket_new(ip, port);

	if (sock == NULL) {
		log_err("Client creation failed: %s", Socket_strerror());
		return NULL;
	}

	return sock;
}

extern void Client_close(Client_T** sock) {
	Socket_free(sock);
}

