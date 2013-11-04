#include "ip.h"
#include "ip_util.h"
#include "debug.h"

extern int IP_subnet_bits_by_hosts_per_subnet(
		IP_T ip, host_size_t hosts_per_subnet) {
	log_debug(
		"Finding suitable subnetting for %lx with %lu hosts/subnet",
		ip, hosts_per_subnet);

	/** hosts/subnet = (2^(host_bits - subnet_bits) - 2)
          * 2^(host_bits - subnet_bits) = hosts/subnet + 2
          * (host_bits - subnet_bits) = log2(hosts/subnet + 2)
	  * subnet_bits = host_bits - log2(hosts/subnet + 2)
	  */
	int aux = hosts_per_subnet + 2;
	int log2 = 0;
	while (aux >>= 1) ++log2;

	if (log2 != 0 && 0UL < hosts_per_subnet) {
		int host_bits = IP_host_bits(ip);
		if (host_bits != -1 && (1 < host_bits - log2)) {
			log_debug("Found %d suitable", host_bits - log2);
			return host_bits - log2;
		}
	}

	IP_set_strerror("IP %lx can't handle %lu hosts/subnet",
		        ip, hosts_per_subnet);
	log_warn("Subnetting bits failed");
	return -1;
}

extern int IP_subnet_bits_by_subnets(
		IP_T ip, subnet_size_t subnets) {
	log_debug("Finding suitable subnetting for %lx with %lu subnets",
		  ip, subnets);

	int comp_bits = IP_subnet_bits_by_hosts_per_subnet(
		ip, (host_size_t)subnets);

	if (comp_bits != -1) {
		log_debug("Found %d suitable", IP_host_bits(ip) - comp_bits);
		return IP_host_bits(ip) - comp_bits;
	}
	log_warn("Subnetting bits failed");
	return -1;
}

