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


static void test_subnets_size(void) {
	assert(IP_subnets_size( 0) == -1);
	assert(IP_subnets_size( 1) == 0UL);
	assert(IP_subnets_size( 5) == 30UL);
	assert(IP_subnets_size(10) == 1022UL);
	assert(IP_subnets_size(15) == 32766UL);
	assert(IP_subnets_size(20) == 1048574UL);
	assert(IP_subnets_size(22) == 4194302UL);
	assert(IP_subnets_size(23) == 8388606UL);
}

int main(int argc, char** argv) {
	test_subnets_size();

	return 0;
}

