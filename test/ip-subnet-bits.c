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

static void test_subnet_bits_by_total_hosts(void) {
	assert(IP_subnet_bits_by_total_hosts(0xc8000000,   0UL) == -1);
	assert(IP_subnet_bits_by_total_hosts(0xc8000000,   1UL) ==  2);
	assert(IP_subnet_bits_by_total_hosts(0xc8000000, 124UL) ==  2);
	assert(IP_subnet_bits_by_total_hosts(0xc8000000, 125UL) ==  3);
	assert(IP_subnet_bits_by_total_hosts(0xc8000000, 180UL) ==  3);
	assert(IP_subnet_bits_by_total_hosts(0xc8000000, 181UL) ==  4);
	assert(IP_subnet_bits_by_total_hosts(0xc8000000, 196UL) ==  4);
	assert(IP_subnet_bits_by_total_hosts(0xc8000000, 197UL) == -1);

	assert(IP_subnet_bits_by_total_hosts(0xa0000000,     0UL) == -1);
	assert(IP_subnet_bits_by_total_hosts(0xa0000000,     1UL) ==  2);
	assert(IP_subnet_bits_by_total_hosts(0xa0000000, 32764UL) ==  2);
	assert(IP_subnet_bits_by_total_hosts(0xa0000000, 32765UL) ==  3);
	assert(IP_subnet_bits_by_total_hosts(0xa0000000, 49140UL) ==  3);
	assert(IP_subnet_bits_by_total_hosts(0xa0000000, 49141UL) ==  4);
	assert(IP_subnet_bits_by_total_hosts(0xa0000000, 57316UL) ==  4);
	assert(IP_subnet_bits_by_total_hosts(0xa0000000, 57317UL) ==  5);
	assert(IP_subnet_bits_by_total_hosts(0xa0000000, 61380UL) ==  5);
	assert(IP_subnet_bits_by_total_hosts(0xa0000000, 61381UL) ==  6);
	assert(IP_subnet_bits_by_total_hosts(0xa0000000, 63364UL) ==  6);
	assert(IP_subnet_bits_by_total_hosts(0xa0000000, 63365UL) ==  7);
	assert(IP_subnet_bits_by_total_hosts(0xa0000000, 64260UL) ==  7);
	assert(IP_subnet_bits_by_total_hosts(0xa0000000, 64261UL) ==  8);
	assert(IP_subnet_bits_by_total_hosts(0xa0000000, 64516UL) ==  8);
	assert(IP_subnet_bits_by_total_hosts(0xa0000000, 64517UL) == -1);

	assert(IP_subnet_bits_by_total_hosts(0x0a000000,        0UL) == -1);
	assert(IP_subnet_bits_by_total_hosts(0x0a000000,        1UL) ==  2);
	assert(IP_subnet_bits_by_total_hosts(0x0a000000,  8388604UL) ==  2);
	assert(IP_subnet_bits_by_total_hosts(0x0a000000,  8388605UL) ==  3);
	assert(IP_subnet_bits_by_total_hosts(0x0a000000, 12582900UL) ==  3);
	assert(IP_subnet_bits_by_total_hosts(0x0a000000, 12582901UL) ==  4);
	assert(IP_subnet_bits_by_total_hosts(0x0a000000, 14680036UL) ==  4);
	assert(IP_subnet_bits_by_total_hosts(0x0a000000, 14680037UL) ==  5);
	assert(IP_subnet_bits_by_total_hosts(0x0a000000, 15728580UL) ==  5);
	assert(IP_subnet_bits_by_total_hosts(0x0a000000, 15728581UL) ==  6);
	assert(IP_subnet_bits_by_total_hosts(0x0a000000, 16252804UL) ==  6);
	assert(IP_subnet_bits_by_total_hosts(0x0a000000, 16252805UL) ==  7);
	assert(IP_subnet_bits_by_total_hosts(0x0a000000, 16514820UL) ==  7);
	assert(IP_subnet_bits_by_total_hosts(0x0a000000, 16514821UL) ==  8);
	assert(IP_subnet_bits_by_total_hosts(0x0a000000, 16645636UL) ==  8);
	assert(IP_subnet_bits_by_total_hosts(0x0a000000, 16645637UL) ==  9);
	assert(IP_subnet_bits_by_total_hosts(0x0a000000, 16710660UL) ==  9);
	assert(IP_subnet_bits_by_total_hosts(0x0a000000, 16710661UL) == 10);
	assert(IP_subnet_bits_by_total_hosts(0x0a000000, 16742404UL) == 10);
	assert(IP_subnet_bits_by_total_hosts(0x0a000000, 16742405UL) == 11);
	assert(IP_subnet_bits_by_total_hosts(0x0a000000, 16756740UL) == 11);
	assert(IP_subnet_bits_by_total_hosts(0x0a000000, 16756741UL) == 12);
	assert(IP_subnet_bits_by_total_hosts(0x0a000000, 16760836UL) == 12);
	assert(IP_subnet_bits_by_total_hosts(0x0a000000, 16760837UL) == -1);
}

static void test_subnet_bits_by_hosts_per_subnet(void) {
	assert(IP_subnet_bits_by_hosts_per_subnet(0xc8000000, 0UL) == -1);
	assert(IP_subnet_bits_by_hosts_per_subnet(0xc8000000, 2UL) == 6);
	assert(IP_subnet_bits_by_hosts_per_subnet(0xc8000000, 6UL) == 5);
	assert(IP_subnet_bits_by_hosts_per_subnet(0xc8000000, 14UL) == 4);
	assert(IP_subnet_bits_by_hosts_per_subnet(0xc8000000, 30UL) == 3);
	assert(IP_subnet_bits_by_hosts_per_subnet(0xc8000000, 62UL) == 2);
	assert(IP_subnet_bits_by_hosts_per_subnet(0xc8000000, 126UL) == -1);
	assert(IP_subnet_bits_by_hosts_per_subnet(0xc8000000, 254UL) == -1);
	assert(IP_subnet_bits_by_hosts_per_subnet(0xc8000000, 255UL) == -1);

	assert(IP_subnet_bits_by_hosts_per_subnet(0xa0000000, 0UL) == -1);
	assert(IP_subnet_bits_by_hosts_per_subnet(0xa0000000, 2UL) == 14);
	assert(IP_subnet_bits_by_hosts_per_subnet(0xa0000000, 6UL) == 13);
	assert(IP_subnet_bits_by_hosts_per_subnet(0xa0000000, 14UL) == 12);
	assert(IP_subnet_bits_by_hosts_per_subnet(0xa0000000, 30UL) == 11);
	assert(IP_subnet_bits_by_hosts_per_subnet(0xa0000000, 62UL) == 10);
	assert(IP_subnet_bits_by_hosts_per_subnet(0xa0000000, 126UL) == 9);
	assert(IP_subnet_bits_by_hosts_per_subnet(0xa0000000, 254UL) == 8);
	assert(IP_subnet_bits_by_hosts_per_subnet(0xa0000000, 510UL) == 7);
	assert(IP_subnet_bits_by_hosts_per_subnet(0xa0000000, 1022UL) == 6);
	assert(IP_subnet_bits_by_hosts_per_subnet(0xa0000000, 2046UL) == 5);
	assert(IP_subnet_bits_by_hosts_per_subnet(0xa0000000, 4094UL) == 4);
	assert(IP_subnet_bits_by_hosts_per_subnet(0xa0000000, 8190UL) == 3);
	assert(IP_subnet_bits_by_hosts_per_subnet(0xa0000000, 16382UL) == 2);
	assert(IP_subnet_bits_by_hosts_per_subnet(0xa0000000, 32766UL) == -1);
	assert(IP_subnet_bits_by_hosts_per_subnet(0xa0000000, 65534UL) == -1);
	assert(IP_subnet_bits_by_hosts_per_subnet(0xa0000000, 65535UL) == -1);

	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 0UL) == -1);
	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 2UL) == 22);
	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 6UL) == 21);
	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 14UL) == 20);
	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 30UL) == 19);
	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 62UL) == 18);
	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 126UL) == 17);
	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 254UL) == 16);
	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 510UL) == 15);
	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 1022UL) == 14);
	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 2046UL) == 13);
	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 4094UL) == 12);
	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 8190UL) == 11);
	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 16382UL) == 10);
	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 32766UL) == 9);
	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 65534UL) == 8);
	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 131070UL) == 7);
	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 262142UL) == 6);
	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 524286UL) == 5);
	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 1048574UL) == 4);
	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 2097150UL) == 3);
	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 4194302UL) == 2);
	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 8388606UL) == -1);
	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 16777214UL) == -1);
	assert(IP_subnet_bits_by_hosts_per_subnet(
	       0x0a000000, 16777215UL) == -1);
}

static void test_subnet_bits_by_subnets(void) {
	assert(IP_subnet_bits_by_subnets(0xc8000000, 0UL) == -1);
	assert(IP_subnet_bits_by_subnets(0xc8000000, 2UL) == 2);
	assert(IP_subnet_bits_by_subnets(0xc8000000, 6UL) == 3);
	assert(IP_subnet_bits_by_subnets(0xc8000000, 14UL) == 4);
	assert(IP_subnet_bits_by_subnets(0xc8000000, 30UL) == 5);
	assert(IP_subnet_bits_by_subnets(0xc8000000, 62UL) == 6);
	assert(IP_subnet_bits_by_subnets(0xc8000000, 126UL) == -1);
	assert(IP_subnet_bits_by_subnets(0xc8000000, 254UL) == -1);
	assert(IP_subnet_bits_by_subnets(0xc8000000, 255UL) == -1);

	assert(IP_subnet_bits_by_subnets(0xa0000000, 0UL) == -1);
	assert(IP_subnet_bits_by_subnets(0xa0000000, 2UL) == 2);
	assert(IP_subnet_bits_by_subnets(0xa0000000, 6UL) == 3);
	assert(IP_subnet_bits_by_subnets(0xa0000000, 14UL) == 4);
	assert(IP_subnet_bits_by_subnets(0xa0000000, 30UL) == 5);
	assert(IP_subnet_bits_by_subnets(0xa0000000, 62UL) == 6);
	assert(IP_subnet_bits_by_subnets(0xa0000000, 126UL) == 7);
	assert(IP_subnet_bits_by_subnets(0xa0000000, 254UL) == 8);
	assert(IP_subnet_bits_by_subnets(0xa0000000, 510UL) == 9);
	assert(IP_subnet_bits_by_subnets(0xa0000000, 1022UL) == 10);
	assert(IP_subnet_bits_by_subnets(0xa0000000, 2046UL) == 11);
	assert(IP_subnet_bits_by_subnets(0xa0000000, 4094UL) == 12);
	assert(IP_subnet_bits_by_subnets(0xa0000000, 8190UL) == 13);
	assert(IP_subnet_bits_by_subnets(0xa0000000, 16382UL) == 14);
	assert(IP_subnet_bits_by_subnets(0xa0000000, 32766UL) == -1);
	assert(IP_subnet_bits_by_subnets(0xa0000000, 65534UL) == -1);
	assert(IP_subnet_bits_by_subnets(0xa0000000, 65535UL) == -1);

	assert(IP_subnet_bits_by_subnets(0x0a000000, 0UL) == -1);
	assert(IP_subnet_bits_by_subnets(0x0a000000, 2UL) == 2);
	assert(IP_subnet_bits_by_subnets(0x0a000000, 6UL) == 3);
	assert(IP_subnet_bits_by_subnets(0x0a000000, 14UL) == 4);
	assert(IP_subnet_bits_by_subnets(0x0a000000, 30UL) == 5);
	assert(IP_subnet_bits_by_subnets(0x0a000000, 62UL) == 6);
	assert(IP_subnet_bits_by_subnets(0x0a000000, 126UL) == 7);
	assert(IP_subnet_bits_by_subnets(0x0a000000, 254UL) == 8);
	assert(IP_subnet_bits_by_subnets(0x0a000000, 510UL) == 9);
	assert(IP_subnet_bits_by_subnets(0x0a000000, 1022UL) == 10);
	assert(IP_subnet_bits_by_subnets(0x0a000000, 2046UL) == 11);
	assert(IP_subnet_bits_by_subnets(0x0a000000, 4094UL) == 12);
	assert(IP_subnet_bits_by_subnets(0x0a000000, 8190UL) == 13);
	assert(IP_subnet_bits_by_subnets(0x0a000000, 16382UL) == 14);
	assert(IP_subnet_bits_by_subnets(0x0a000000, 32766UL) == 15);
	assert(IP_subnet_bits_by_subnets(0x0a000000, 65534UL) == 16);
	assert(IP_subnet_bits_by_subnets(0x0a000000, 131070UL) == 17);
	assert(IP_subnet_bits_by_subnets(0x0a000000, 262142UL) == 18);
	assert(IP_subnet_bits_by_subnets(0x0a000000, 524286UL) == 19);
	assert(IP_subnet_bits_by_subnets(0x0a000000, 1048574UL) == 20);
	assert(IP_subnet_bits_by_subnets(0x0a000000, 2097150UL) == 21);
	assert(IP_subnet_bits_by_subnets(0x0a000000, 4194302UL) == 22);
	assert(IP_subnet_bits_by_subnets(0x0a000000, 8388606UL) == -1);
	assert(IP_subnet_bits_by_subnets(0x0a000000, 16777214UL) == -1);
	assert(IP_subnet_bits_by_subnets(0x0a000000, 16777215UL) == -1);
}

int main(int argc, char** argv) {
	test_subnet_bits_by_total_hosts();
	test_subnet_bits_by_hosts_per_subnet();
	test_subnet_bits_by_subnets();

	return 0;
}

