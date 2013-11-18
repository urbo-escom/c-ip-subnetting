#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "subnet-calc.h"
#include "subnet-calc-util.h"

static char info[1025];

#define check(b, info, ...) do{\
	if(b) { sprintf(info, ##__VA_ARGS__); return info;\
	} } while(0)

extern char* SubnetCalc_subnetting_by_hosts(
		host_size_t hosts, int id, Subnet subnet_number) {
	int host_bits = IP_host_bits_by_total_hosts(hosts);
	IP_T ip = IP_private_ip(host_bits, id);
	check(host_bits == -1 || ip == -1, info,
	      "error Too many hosts, %lu for %lx or private ip failed",
	      ip, hosts);

	return SubnetCalc_subnetting_by_ip_and_hosts(
		ip, hosts, subnet_number);
}

extern char* SubnetCalc_subnetting_by_hosts_per_subnet(
		host_size_t hosts_per_subnet, int id, Subnet subnet_number) {
	int host_bits = IP_host_bits_by_hosts_per_subnet(hosts_per_subnet);
	IP_T ip = IP_private_ip(host_bits, id);
	check(host_bits == -1 || ip == -1, info,
	      "error Too many hosts/subnet, %lu for %lx or private ip failed",
	      ip, hosts_per_subnet);

	return SubnetCalc_subnetting_by_ip_and_hosts(
		ip, hosts_per_subnet, subnet_number);
}

extern char* SubnetCalc_subnetting_by_subnets(
		subnet_size_t subnets, int id, Subnet subnet_number) {
	int host_bits = IP_host_bits_by_subnets(subnets);
	IP_T ip = IP_private_ip(host_bits, id);
	check(host_bits == -1 || ip == -1, info,
	      "error Too many subnets, %lu for %lx or private ip failed",
	      ip, subnets);

	return SubnetCalc_subnetting_by_ip_and_subnets(
		ip, subnets, subnet_number);
}

