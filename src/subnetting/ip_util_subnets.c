#include "ip.h"
#include "ip_util.h"
#include "debug.h"

static subnet_size_t max_subnets(int host_bits) {
	return ((1L << (host_bits - 2)) - 2);
}

extern int IP_host_bits_by_subnets(subnet_size_t subnets) {
	int hosts[3] = {8, 16, 24};

	log_debug("Finding suitable Class for %lu subnets", subnets);
	int i;
	for(i = 0; i < sizeof(hosts)/sizeof(int); i++) {
		log_debug("---%d bits", hosts[i]);
		if (subnets <= max_subnets(hosts[i])) {
			log_debug("Found with %d bits", hosts[i]);
			return hosts[i];
		}
	}

	IP_set_strerror("Too many subnets: %lu", subnets);
	log_warn("Too many subnets: %lu", subnets);
	return -1;
}

