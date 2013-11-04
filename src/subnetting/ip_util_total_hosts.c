#include "ip.h"
#include "ip_util.h"
#include "debug.h"

static host_size_t max_hosts(int host_bits) {
	return ((1L << (host_bits/2)) - 2)*
	       ((1L << (host_bits/2)) - 2);
}

extern int IP_host_bits_by_total_hosts(host_size_t total_hosts) {
	int hosts[3] = {8, 16, 24};

	log_debug("Finding suitable Class for %lu hosts", total_hosts);
	int i;
	for(i = 0; i < sizeof(hosts)/sizeof(int); i++) {
		log_debug("---%d bits", hosts[i]);
		if (total_hosts <= max_hosts(hosts[i])) {
			log_debug("Found with %d bits", hosts[i]);
			return hosts[i];
		}
	}

	IP_set_strerror("Too many hosts: %lu", total_hosts);
	log_warn("Too many hosts: %lu", total_hosts);
	return -1;
}

