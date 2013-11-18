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


static void test_host_bits_by_total_hosts(void) {
	assert(IP_host_bits_by_total_hosts(       0UL) == 8);
	assert(IP_host_bits_by_total_hosts(     128UL) == 8);
	assert(IP_host_bits_by_total_hosts(     196UL) == 8);
	assert(IP_host_bits_by_total_hosts(     197UL) == 16);
	assert(IP_host_bits_by_total_hosts(   64516UL) == 16);
	assert(IP_host_bits_by_total_hosts(   64517UL) == 24);
	assert(IP_host_bits_by_total_hosts(16760836UL) == 24);
	assert(IP_host_bits_by_total_hosts(16760837UL) == -1);
	assert(IP_host_bits_by_total_hosts(0xffffffff) == -1);
}

int main(int argc, char** argv) {
	test_host_bits_by_total_hosts();

	return 0;
}

