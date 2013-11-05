#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exchange.h"
#include "debug.h"

static int listen(const char* request, char* response, int size);

static char program[129];

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Usage: %s port\n", argv[0]);
		return 1;
	}

	strncpy(program, argv[0], 129);

	Server_T* server = Server_create(argv[1]);

	if (server == NULL) {
		printf("Server creation failed\n");
		return 1;
	}

	if (Server_init(server, listen) != 0)
		printf("An error happened\n");

	Server_close(&server);

	return 0;
}

static int option(const char* s) {
	if (strcmp(s, "time") == 0 || strcmp(s, "time\r\n") == 0)
		return 0;
	if (strcmp(s, "name") == 0 || strcmp(s, "name\r\n") == 0)
		return 1;
	if (strcmp(s, "hello") == 0 || strcmp(s, "hello\r\n") == 0)
		return 2;
	if (strcmp(s, "shutdown") == 0 || strcmp(s, "shutdown\r\n") == 0)
		return 3;
	return -1;
}

static int listen(const char* request, char* response, int size) {
	switch(option(request)) {
		case 0:
			snprintf(response, size, "Time:%s", get_time());
			break;
		case 1:
			snprintf(response, size, "I am %s", program);
			break;
		case 2:
			snprintf(response, size, "hello world!");
			break;
		case 3:
			snprintf(response, size, "shutdown NOW");
			return 1;
			break;
		default:
			snprintf(response, size, "reflect: %s", request);
			break;
	}
	return 0;
}

