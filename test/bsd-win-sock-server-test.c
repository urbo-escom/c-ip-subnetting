#include <stdio.h>
#include <stdlib.h>

#include "bsd-win-sock.h"
#include "debug.h"

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Usage: %s port\n", argv[0]);
		return 1;
	}

	printf("Port    %s\n", argv[1]);

	Socket_T* socket = Socket_new(NULL, argv[1]);

	if (socket == NULL) {
		log_err("Server not created: %s", Socket_strerror());
		return 1;
	}

	if (Socket_bind(socket) != 0) {
		log_err("Can't bind: %s", Socket_strerror());
		Socket_free(&socket);
		return 1;
	}

	if (Socket_listen(socket, 5) != 0) {
		log_err("Can't listen: %s", Socket_strerror());
		Socket_free(&socket);
		return 1;
	}

	int status = 1;
	for(;status != 0;) {

		if (Socket_accept(socket) != 0) {
			log_err("Can't accept: %s", Socket_strerror());
			Socket_free(&socket);
			return 1;
		}

		if (Socket_timeout(socket, 10) != 0) {
			log_err("Can't set timeout: %s", Socket_strerror());
			Socket_free(&socket);
			return -1;
		}

		char request[1025];
		memset(request, 0, sizeof(request));
		if (Socket_receive(socket, request, 1025) == -1)
			log_warn("Error while receiving: %s",
			         Socket_strerror());
		else
			printf("Received: %s\n", request);

		if (strcmp("shutdown", request) == 0 ||
		    strcmp("shutdown\r\n", request) == 0)
			status = 0;

		sprintf(request + strlen(request), " - len= %d",
		        strlen(request));

		if (Socket_send(socket, request, strlen(request)) !=
		    strlen(request))
			log_warn("Error while sending: %s", Socket_strerror());
		else
			printf("Sent: %s\n", request);
	}

	Socket_free(&socket);
	return 0;
}

