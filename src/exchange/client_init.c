#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

#include "bsd-win-sock.h"
#include "exchange.h"
#include "debug.h"

extern int  Client_init(
		Client_T* sock,
		int (*request)(
			char* request, const char* response, int size)) {
	if (Socket_connect(sock) < 0) {
		log_err("Socket connect failed: %s", Socket_strerror());
		return -1;
	}

	Socket_timeout(sock, 5);
	char request_s[65537];
	char response[65537];
	int bytes_recv;
	int bytes_sent;
	int status;
	memset(response, 0, sizeof(response));
	request(request_s, response, 65537);
	do {
		log_info("Server: %s:%s",
		         Socket_get_ip(sock), Socket_get_port(sock));

		bytes_sent = Socket_send(sock, request_s, strlen(request_s));
		if (bytes_sent == -1)
			log_warn("Error at sending request");

		bytes_recv = Socket_receive(sock, response, 65537);
		if (bytes_recv == -1) {
			log_warn("Error at receiving response");
		} else {
			log_debug("Client received '%.*s'", bytes_recv,
			          response);
		}

		status = request(request_s, response, 65537);
	} while(status == 0);
	return 0;
}

