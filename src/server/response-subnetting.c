#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "response.h"

static char info[1025];

static int parse(const char* s, unsigned long int* l,
		int* id, Subnet* subnet) {
	return sscanf(s, "%*s %lu %d %lu", l, id, subnet) == 3;
}

#define parse_and_check(request, l, id, subnet) do{\
		if (!parse(request, l, id, subnet)) {\
			sprintf(info, "error Missing/invalid arguments");\
			return info;\
		}\
	} while(0)

extern char* subnetting_by_hosts(const char* request) {
	host_size_t hosts;
	int id;
	Subnet num;
	parse_and_check(request, &hosts, &id, &num);

	return SubnetCalc_subnetting_by_hosts(hosts, id, num);
}

extern char* subnetting_by_hosts_per_subnet(const char* request) {
	host_size_t hosts_per_subnet;
	int id;
	Subnet num;
	parse_and_check(request, &hosts_per_subnet, &id, &num);

	return SubnetCalc_subnetting_by_hosts_per_subnet(
		hosts_per_subnet, id, num);
}

extern char* subnetting_by_subnets(const char* request) {
	subnet_size_t subnets;
	int id;
	Subnet num;
	parse_and_check(request, &subnets, &id, &num);

	return SubnetCalc_subnetting_by_subnets(subnets, id, num);
}

