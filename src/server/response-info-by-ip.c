#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "response.h"

static char info[1205];

static int parse(const char* s, IP_T* ip, unsigned long int* l) {
	char aux[1025];
	return sscanf(s, "%*s %s %lu", aux, l) == 2 &&
	       IP_dot_decimal_to_ip(aux, ip) == 0;
}

extern char* info_by_ip_and_hosts(const char* request) {
	IP_T ip;
	host_size_t hosts;

	if (!parse(request, &ip, &hosts)) {
		sprintf(info, "error Missing/invalid arguments or wrong IP");
		return info;
	}

	return SubnetCalc_get_info_by_ip_and_hosts(ip, hosts);
}

extern char* info_by_ip_and_hosts_per_subnet(const char* request) {
	IP_T ip;
	host_size_t hosts;

	if (!parse(request, &ip, &hosts)) {
		sprintf(info, "error Missing/invalid arguments or wrong IP");
		return info;
	}
	return SubnetCalc_get_info_by_ip_and_hosts_per_subnet(ip, hosts);
}

extern char* info_by_ip_and_subnets(const char* request) {
	IP_T ip;
	subnet_size_t subnets;

	if (!parse(request, &ip, &subnets)) {
		sprintf(info, "error Missing/invalid arguments or wrong IP");
		return info;
	}

	return SubnetCalc_get_info_by_ip_and_subnets(ip, subnets);
}

