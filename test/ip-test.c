#include <stdlib.h>
#include <stdio.h>

#include "ip.h"

#define assert(s) do{\
	if (s)\
		printf("Test succeded: '" #s "'\n");\
	else\
		printf("Test FAILED: '" #s "'\n");\
	} while(0)

static void test_host_bits(void) {
	assert(IP_host_bits(0x00000000) == 24);
	assert(IP_host_bits(0x0a234000) == 24);
	assert(IP_host_bits(0x7f007600) == 24);
	assert(IP_host_bits(0x80000000) == 16);
	assert(IP_host_bits(0xae034000) == 16);
	assert(IP_host_bits(0xbfffffff) == 16);
	assert(IP_host_bits(0xc0000000) ==  8);
	assert(IP_host_bits(0xca000000) ==  8);
	assert(IP_host_bits(0xdfffffff) ==  8);
	assert(IP_host_bits(0xe0000000) == -1);
	assert(IP_host_bits(0xeabcdef0) == -1);
	assert(IP_host_bits(0xffffffff) == -1);
}

static void test_class(void) {
	assert(IP_class(0x00000000) == 'A');
	assert(IP_class(0x0a234000) == 'A');
	assert(IP_class(0x7f007600) == 'A');
	assert(IP_class(0x80000000) == 'B');
	assert(IP_class(0xae034000) == 'B');
	assert(IP_class(0xbfffffff) == 'B');
	assert(IP_class(0xc0000000) == 'C');
	assert(IP_class(0xca000000) == 'C');
	assert(IP_class(0xdfffffff) == 'C');
	assert(IP_class(0xe0000000) ==  -1);
	assert(IP_class(0xeabcdef0) ==  -1);
	assert(IP_class(0xffffffff) ==  -1);
}

static void test_mask(void) {
	assert(IP_mask(0x00000000) == 0xff000000);
	assert(IP_mask(0x0a234000) == 0xff000000);
	assert(IP_mask(0x7f007600) == 0xff000000);
	assert(IP_mask(0x80000000) == 0xffff0000);
	assert(IP_mask(0xae034000) == 0xffff0000);
	assert(IP_mask(0xbfffffff) == 0xffff0000);
	assert(IP_mask(0xc0000000) == 0xffffff00);
	assert(IP_mask(0xca000000) == 0xffffff00);
	assert(IP_mask(0xdfffffff) == 0xffffff00);
	assert(IP_mask(0xe0000000) == 0x00000000);
	assert(IP_mask(0xeabcdef0) == 0x00000000);
	assert(IP_mask(0xffffffff) == 0x00000000);
}

static void test_broadcast(void) {
	assert(IP_broadcast(0x00000000) == 0x00ffffff);
	assert(IP_broadcast(0x0a234000) == 0x0affffff);
	assert(IP_broadcast(0x7f007600) == 0x7fffffff);
	assert(IP_broadcast(0x80000000) == 0x8000ffff);
	assert(IP_broadcast(0xae034000) == 0xae03ffff);
	assert(IP_broadcast(0xbfffffff) == 0xbfffffff);
	assert(IP_broadcast(0xc0000000) == 0xc00000ff);
	assert(IP_broadcast(0xca000000) == 0xca0000ff);
	assert(IP_broadcast(0xdfffffff) == 0xdfffffff);
	assert(IP_broadcast(0xe0000000) == 0xffffffff);
	assert(IP_broadcast(0xeabcdef0) == 0xffffffff);
	assert(IP_broadcast(0xffffffff) == 0xffffffff);
}

static void test_is_valid_id(void) {
	assert(IP_is_valid_id(0x00000000) == 1);
	assert(IP_is_valid_id(0x0a234000) == 0);
	assert(IP_is_valid_id(0x7f007600) == 0);
	assert(IP_is_valid_id(0x80000000) == 1);
	assert(IP_is_valid_id(0xae034000) == 0);
	assert(IP_is_valid_id(0xbfffffff) == 0);
	assert(IP_is_valid_id(0xc0000000) == 1);
	assert(IP_is_valid_id(0xca000000) == 1);
	assert(IP_is_valid_id(0xdfffffff) == 0);
	assert(IP_is_valid_id(0xe0000000) == 0);
	assert(IP_is_valid_id(0xeabcdef0) == 0);
	assert(IP_is_valid_id(0xffffffff) == 0);
}

int main(int argc, char** argv) {
	test_host_bits();
	test_class();
	test_mask();
	test_broadcast();
	test_is_valid_id();

	return 0;
}

