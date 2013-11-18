#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "init.h"

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Usage:%s port\n", argv[0]);
		exit(1);
	}

	printf("Initializing with port %s\n", argv[1]);

	return start_server(argv[1]);
}

