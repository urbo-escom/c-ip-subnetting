#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "response.h"

static char info[1025];

static int parse(const char* s, unsigned long int* l, int* id) {
	return sscanf(s, "%*s %d %lu", id, l) == 2;
}

extern char* info_by_hosts(const char* request) {
	host_size_t hosts;
	int id;

	if(!parse(request, &hosts, &id)) {
		sprintf(info, "error Missing/invalid arguments");
		return info;
	}

	return SubnetCalc_get_info_by_hosts(hosts, id);
}

extern char* info_by_hosts_per_subnet(const char* request) {
	host_size_t hosts_per_subnet;
	int id;

	if(!parse(request, &hosts_per_subnet, &id)) {
		sprintf(info, "error Missing/invalid arguments");
		return info;
	}

	return SubnetCalc_get_info_by_hosts_per_subnet(hosts_per_subnet, id);
}

extern char* info_by_subnets(const char* request) {
	subnet_size_t subnets;
	int id;

	if(!parse(request, &subnets, &id)) {
		sprintf(info, "error Missing/invalid arguments");
		return info;
	}

	return SubnetCalc_get_info_by_subnets(subnets, id);
}

