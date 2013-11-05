#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bsd-win-sock.h"
#include "exchange.h"
#include "debug.h"

extern int Server_init(
		Server_T* sock,
		int (*response)(
			const char* request, char* response, int size)) {
	char request[65537];
	char response_s[65537];
	int bytes_recv;
	int bytes_sent;
	int status;
	do {
		status = Socket_accept(sock);
		if (status != 0) {
			log_err("Server accept failed %s", Socket_strerror());
			return -1;
		}

		log_info("Client: %s:%s",
		         Socket_get_ip(sock),
		         Socket_get_port(sock));

		bytes_recv = Socket_receive(sock, request, 65537);

		if (bytes_recv == -1)
			status = response("\0", response_s, 65537);
		else
			status = response(request, response_s, 65537);

		bytes_sent = Socket_send(sock, response_s,
		                         strlen(response_s));

		if (bytes_sent == -1) {
			log_warn("Server sending failed");
		} else {
			log_debug("Server sent '%.*s'",
			          bytes_sent, response_s);
			Socket_send(sock, "\0", strlen("\0"));
		}
	} while(status == 0);
	return 0;
}

