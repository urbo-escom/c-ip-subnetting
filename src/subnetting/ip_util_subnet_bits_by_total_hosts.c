#include "ip.h"
#include "ip_util.h"
#include "debug.h"

static host_size_t get_hosts_per_subnet(IP_T ip, int subnet_bits) {
	return (1L << (IP_host_bits(ip) - subnet_bits)) - 2;
}

static subnet_size_t get_total_subnets(IP_T ip, int subnet_bits) {
	return (1L << subnet_bits) - 2;
}

extern int IP_subnet_bits_by_total_hosts(
		IP_T ip, host_size_t total_hosts) {
	int i;
	int host_bits = IP_host_bits(ip);
	host_size_t hosts_per_subnet;
	host_size_t total_subnets;
	host_size_t total;

	log_debug(
		"Searching suitable subnetting for %lx with %lu total hosts",
		ip, total_hosts);
	for(i = 2; i < host_bits - 1; i++) {
		hosts_per_subnet = get_hosts_per_subnet(ip, i);
		total_subnets = get_total_subnets(ip, i);
		total = hosts_per_subnet*total_subnets;

		log_debug("---hosts/subnet: %lu", hosts_per_subnet);
		log_debug("---total subnets: %lu", total_subnets);
		log_debug("---total hosts: %lu", total);
		if (total_hosts <= total) {
			log_debug("Found with %d bits", i);
			return i;
		}
	}

	IP_set_strerror(
		"IP %lx can't handle %lu total hosts",
		ip, total_hosts);
	log_warn("Subnetting bits failed");
	return -1;
}

extern subnet_size_t IP_subnets_size(int subnet_bits) {
	return (1L << subnet_bits) - 2;
}

