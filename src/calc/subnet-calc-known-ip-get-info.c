#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "subnet-calc.h"
#include "subnet-calc-util.h"

static char info[1025];

#define check(b, info, ...) do{\
	if(b) { sprintf(info, ##__VA_ARGS__); return info;\
	} } while(0)

/* Known IP's (Format: "ip class subnet_bits subnets_size") */
extern char* SubnetCalc_get_info_by_ip_and_hosts(
		IP_T ip, host_size_t hosts) {
	int subnet_bits = IP_subnet_bits_by_total_hosts(ip, hosts);

	check(subnet_bits == -1, info, "error Too many hosts (%lu) for %lx",
	      hosts, ip);

	return SubnetCalcUtil_get_info(ip, subnet_bits);
}

extern char* SubnetCalc_get_info_by_ip_and_hosts_per_subnet(
		IP_T ip, host_size_t hosts_per_subnet) {
	int subnet_bits =
		IP_subnet_bits_by_hosts_per_subnet(ip, hosts_per_subnet);

	check(subnet_bits == -1, info, "error "
	      "Too many hosts per subnet (%lu) for %lx",
	      hosts_per_subnet, ip);

	return SubnetCalcUtil_get_info(ip, subnet_bits);
}

extern char* SubnetCalc_get_info_by_ip_and_subnets(
		IP_T ip, subnet_size_t subnets) {
	int subnet_bits = IP_subnet_bits_by_subnets(ip, subnets);

	check(subnet_bits == -1, info, "error Too many subnets (%lu) for %lx",
	      subnets, ip);

	return SubnetCalcUtil_get_info(ip, subnet_bits);
}

