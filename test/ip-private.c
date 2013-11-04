#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ip.h"
#include "ip_util.h"

#define assert(s) do{\
	if (s)\
		printf("Test succeded: '" #s "'\n");\
	else\
		printf("Test FAILED: '" #s "'\n");\
	} while(0)

static void test_private_ip(void) {
	IP_T ip;

	assert((ip = (IP_private_ip(24, 255) >> 24)) &&
	         0UL <  ip && ip < 128UL);
	assert((ip = (IP_private_ip(16, 255) >> 24)) &&
	       128UL <= ip && ip < 192UL);
	assert((ip = (IP_private_ip( 8, 255) >> 24)) &&
	       192UL <= ip && ip < 224UL);
	assert((ip = (IP_private_ip( 9, 255))) &&
	       ip == -1);
}

int main(int argc, char** argv) {
	test_private_ip();

	return 0;
}

