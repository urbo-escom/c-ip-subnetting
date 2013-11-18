#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "init.h"
#include "exchange.h"

extern int start_server(const char* port) {
	Server_T* server = Server_create(port);

	if (server == NULL) {
		printf("Server creation failed\n");
		return 1;
	}

	if (Server_init(server, &calc) != 0)
		printf("An error happened\n");

	Server_close(&server);

	return 0;
}

