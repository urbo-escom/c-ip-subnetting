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

static void test_dot_decimal_to_ip(void) {
	IP_T ip = 0UL;
	assert(IP_dot_decimal_to_ip("0.0.0.0", &ip) == 0 &&
	       ip == 0x00000000);
	assert(IP_dot_decimal_to_ip("10.35.64.0", &ip) == 0 &&
	       ip == 0x0a234000);
	assert(IP_dot_decimal_to_ip("127.0.118.0", &ip) == 0 &&
	       ip == 0x7f007600);

	assert(IP_dot_decimal_to_ip("128.0.0.0", &ip) == 0 &&
	       ip == 0x80000000);
	assert(IP_dot_decimal_to_ip("174.3.64.0", &ip) == 0 &&
	       ip == 0xae034000);
	assert(IP_dot_decimal_to_ip("191.255.255.255", &ip) == 0 &&
	       ip == 0xbfffffff);

	assert(IP_dot_decimal_to_ip("192.0.0.0", &ip) == 0 &&
	       ip == 0xc0000000);
	assert(IP_dot_decimal_to_ip("202.171.205.239", &ip) == 0 &&
	       ip == 0xcaabcdef);
	assert(IP_dot_decimal_to_ip("223.255.255.255", &ip) == 0 &&
	       ip == 0xdfffffff);

	ip = 0UL;
	assert(IP_dot_decimal_to_ip("224.0.0.0", &ip) == -1 &&
	       ip == 0x00000000);
	assert(IP_dot_decimal_to_ip("234.202.202.190", &ip) == -1 &&
	       ip == 0x00000000);
	assert(IP_dot_decimal_to_ip("255.255.255.255", &ip) == -1 &&
	       ip == 0x00000000);
}

static void test_ip_to_dot_decimal(void) {
	char address[65];
	memset(address, 0, sizeof(address));

	assert(IP_ip_to_dot_decimal(0x00000000, address) == 0 &&
	       strcmp(address, "0.0.0.0") == 0);
	assert(IP_ip_to_dot_decimal(0x0a234000, address) == 0 &&
	       strcmp(address, "10.35.64.0") == 0);
	assert(IP_ip_to_dot_decimal(0x7f007600, address) == 0 &&
	       strcmp(address, "127.0.118.0") == 0);

	assert(IP_ip_to_dot_decimal(0x80000000, address) == 0 &&
	       strcmp(address, "128.0.0.0") == 0);
	assert(IP_ip_to_dot_decimal(0xae034000, address) == 0 &&
	       strcmp(address, "174.3.64.0") == 0);
	assert(IP_ip_to_dot_decimal(0xbfffffff, address) == 0 &&
	       strcmp(address, "191.255.255.255") == 0);

	assert(IP_ip_to_dot_decimal(0xc0000000, address) == 0 &&
	       strcmp(address, "192.0.0.0") == 0);
	assert(IP_ip_to_dot_decimal(0xcaabcdef, address) == 0 &&
	       strcmp(address, "202.171.205.239") == 0);
	assert(IP_ip_to_dot_decimal(0xdfffffff, address) == 0 &&
	       strcmp(address, "223.255.255.255") == 0);

	assert(IP_ip_to_dot_decimal(0xe0000000, address) == 0 &&
	       strcmp(address, "224.0.0.0") == 0);
	assert(IP_ip_to_dot_decimal(0xeacacabe, address) == 0 &&
	       strcmp(address, "234.202.202.190") == 0);
	assert(IP_ip_to_dot_decimal(0xffffffff, address) == 0 &&
	       strcmp(address, "255.255.255.255") == 0);
}

int main(int argc, char** argv) {
	test_dot_decimal_to_ip();
	test_ip_to_dot_decimal();

	return 0;
}

