#include <stdio.h>
#include <stdlib.h>

#include "bsd-win-sock.h"
#include "debug.h"

int main(int argc, char** argv) {
	if (argc != 4) {
		printf("Usage: %s ip port request\n", argv[0]);
		return -1;
	}

	printf("IP      %s\n", argv[1]);
	printf("Port    %s\n", argv[2]);
	printf("Request %s\n", argv[3]);

	Socket_T* socket = Socket_new(argv[1], argv[2]);

	if (socket == NULL) {
		log_err("Client not created: %s", Socket_strerror());
		return -1;
	}

	if (Socket_connect(socket) != 0) {
		log_err("Can't connect: %s", Socket_strerror());
		Socket_free(&socket);
		return -1;
	}

	if (Socket_timeout(socket, 10) != 0) {
		log_err("Can't set timeout: %s", Socket_strerror());
		Socket_free(&socket);
		return -1;
	}

	if (Socket_send(socket, argv[3], strlen(argv[3])) !=
	    strlen(argv[3]))
		log_warn("Error while sending: %s", Socket_strerror());

	char response[1025];
	if (Socket_receive(socket, response, 1025) == -1)
		log_warn("Error while receiving: %s", Socket_strerror());
	else
		printf("Received: %s\n", response);

	Socket_free(&socket);
	return 0;
}

