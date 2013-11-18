#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "response.h"

static char info[1025];

static int parse(const char* s, IP_T* ip, unsigned long int* l, Subnet* id) {
	char aux[1025];
	return sscanf(s, "%*s %s %lu %lu", aux, l, id) == 3 &&
	       IP_dot_decimal_to_ip(aux, ip) == 0;
}

#define parse_and_check(request, ip, l, subnet) do{\
		if (!parse(request, ip, l, subnet)) {\
			sprintf(info, "error Missing/invalid arguments");\
			return info;\
		}\
	} while(0)

extern char* subnetting_by_ip_and_hosts(const char* request) {
	IP_T ip;
	host_size_t hosts;
	Subnet num;
	parse_and_check(request, &ip, &hosts, &num);

	return SubnetCalc_subnetting_by_ip_and_hosts(ip, hosts, num);
}

extern char* subnetting_by_ip_and_hosts_per_subnet(const char* request) {
	IP_T ip;
	host_size_t hosts_per_subnet;
	Subnet num;
	parse_and_check(request, &ip, &hosts_per_subnet, &num);

	return SubnetCalc_subnetting_by_ip_and_hosts_per_subnet(
		ip, hosts_per_subnet, num);
}

extern char* subnetting_by_ip_and_subnets(const char* request) {
	IP_T ip;
	subnet_size_t subnets;
	Subnet num;
	parse_and_check(request, &ip, &subnets, &num);

	return SubnetCalc_subnetting_by_ip_and_subnets(ip, subnets, num);
}

