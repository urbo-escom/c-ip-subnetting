#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "subnet-calc.h"
#include "subnet-calc-util.h"

static char info[1025];

#define check(b, info, ...) do{\
	if(b) { sprintf(info, ##__VA_ARGS__); return info;\
	} } while(0)

/* Known IP's (Format: "# Use id broadcast mask host-start host-end") */
extern char* SubnetCalc_subnetting_by_ip_and_hosts(
		IP_T ip, host_size_t hosts, Subnet subnet_number) {
	int subnet_bits = IP_subnet_bits_by_total_hosts(ip, hosts);

	check(subnet_bits == -1, info,
	      "error Too many hosts (%lu) for %lx", ip, hosts);

	return SubnetCalcUtil_subnetting(ip, subnet_bits, subnet_number);
}

extern char* SubnetCalc_subnetting_by_ip_and_hosts_per_subnet(
		IP_T ip, host_size_t hosts_per_subnet, Subnet subnet_number) {
	int subnet_bits =
		IP_subnet_bits_by_hosts_per_subnet(ip, hosts_per_subnet);

	check(subnet_bits == -1, info,
	      "error Too many hosts per subnet (%lu) for %lx",
	      ip, hosts_per_subnet);

	return SubnetCalcUtil_subnetting(ip, subnet_bits, subnet_number);
}

extern char* SubnetCalc_subnetting_by_ip_and_subnets(
		IP_T ip, subnet_size_t subnets, Subnet subnet_number) {
	int subnet_bits = IP_subnet_bits_by_subnets(ip, subnets);

	check(subnet_bits == -1, info,
	      "error Too many subnets (%lu) for %lx", ip, subnets);

	return SubnetCalcUtil_subnetting(ip, subnet_bits, subnet_number);
}

