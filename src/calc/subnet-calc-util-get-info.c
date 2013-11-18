#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "subnet-calc-util.h"

static char info[1025];
static char ip_s[65];

/* (Format: "ip class subnet_bits subnets_size") */ 
extern char* SubnetCalcUtil_get_info(
		IP_T ip, int subnet_bits) {
	if (!IP_is_valid_id(ip)) {
		snprintf(info, 1025, "error Invalid ID for %lx", ip);
		return info;
	}

	if (!(1 < subnet_bits && subnet_bits < IP_host_bits(ip) - 1)) {
		snprintf(info, 1025, "error "
			"Inadequate subnet bits (%d bits) for %lx",
			subnet_bits, ip);
		return info;
	}

	if (IP_ip_to_dot_decimal(ip, ip_s) == -1) {
		snprintf(info, 1025, "error At conversion of %lx: %s",
		         ip, IP_strerror());
		return info;
	}

	snprintf(info, 1025, "%s %c %d %lu", ip_s, IP_class(ip),
	         subnet_bits, IP_subnets_size(subnet_bits));
	return info;
}

