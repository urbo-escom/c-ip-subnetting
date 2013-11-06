#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exchange.h"

static int listen(char* request, const char* response, int size);

static int count = 0;

static char msg[129];

int main(int argc, char** argv) {
	if (argc != 4) {
		printf("Usage: %s ip port message\n", argv[0]);
		return 1;
	}

	strncpy(msg, argv[3], 129);

	Client_T* client = Client_create(argv[1], argv[2]);

	if (client == NULL) {
		printf("Client creation failed\n");
		return 1;
	}

	if (Client_init(client, listen) != 0)
		printf("An error happened\n");

	Client_close(&client);

	return 0;
}

static int option(const char* s) {
	if (s == NULL || strlen(s) == 0)
		return 0;
	if (strcmp(s, "shutdown NOW") == 0 ||
	    strcmp(s, "shutdown NOW\r\n") == 0)
		return 1;
	return -1;
}

static int listen(char* request, const char* response, int size) {
	switch(option(request)) {
		case 0:
			snprintf(request, size, "%s", msg);
			break;
		case 1:
			snprintf(request, size, "Bye");
			return 1;
			break;
		default:
			printf("Client received: '%s'\n", response);
			snprintf(request, size, "%s", msg);
			break;
	}
	count++;
	return !(count < 1);
}

