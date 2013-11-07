#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "subnet-calc.h"
#include "subnet-calc-util.h"

static char info[1025];

#define check(b, info, ...) do{\
	if(b) { sprintf(info, ##__VA_ARGS__); return info;\
	} } while(0)

static char info[1025];

extern char* SubnetCalc_get_info_by_hosts(
		host_size_t hosts, int id) {
	int host_bits = IP_host_bits_by_total_hosts(hosts);
	IP_T ip = IP_private_ip(host_bits, id);
	check(host_bits == -1 || ip == -1, info,
	      "error Too many hosts, %lu for %lx or IP private failed",
	      hosts, ip);

	return SubnetCalc_get_info_by_ip_and_hosts(ip, hosts);
}

extern char* SubnetCalc_get_info_by_hosts_per_subnet(
		host_size_t hosts_per_subnet, int id) {
	int host_bits = IP_host_bits_by_hosts_per_subnet(hosts_per_subnet);
	IP_T ip = IP_private_ip(host_bits, id);
	check(host_bits == -1 || ip == -1, info,
	      "error Too many hosts/subnet, %lu for %lx or IP private failed",
	      hosts_per_subnet, ip);

	return SubnetCalc_get_info_by_ip_and_hosts_per_subnet(
		ip, hosts_per_subnet);
}

extern char* SubnetCalc_get_info_by_subnets(
		subnet_size_t subnets, int id) {
	int host_bits = IP_host_bits_by_subnets(subnets);
	IP_T ip = IP_private_ip(host_bits, id);
	check(host_bits == -1 || ip == -1, info,
	      "error Too many subnets, %lu for %lx or IP private failed",
	      subnets, ip);

	return SubnetCalc_get_info_by_ip_and_subnets(ip, subnets);
}

