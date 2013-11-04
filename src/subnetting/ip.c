#include "ip.h"
#include "debug.h"

extern int IP_host_bits(IP_T ip) {
	IP_T prefix = ip >> 24;

	log_debug("Getting host bits %lx -> %lx", ip, prefix);
	if (  0UL <= prefix && prefix < 128UL) /* Class A */
		return 24;
	if (128UL <= prefix && prefix < 192UL) /* Class B */
		return 16;
	if (192UL <= prefix && prefix < 224UL) /* Class C */
		return 8;

	IP_set_strerror("Unkown class %lx", ip);
	return -1;
}

extern char IP_class(IP_T ip) {
	switch(IP_host_bits(ip)) {
		case 24: return 'A';
		case 16: return 'B';
		case  8: return 'C';
		default: return -1;
	}
}

extern IP_T IP_mask(IP_T ip) {
	int host_bits = IP_host_bits(ip);
	log_debug("%lx-mask-%lx", ip, (-1L) << (host_bits));
	return host_bits == -1? 0UL:(-1L) << (host_bits);
}

extern IP_T IP_broadcast(IP_T ip) {
	int host_bits = IP_host_bits(ip);
	/* NNN...(N + 1)000...0 - 1 = NNN...N111...1 */
	return host_bits == -1? -1:(ip & IP_mask(ip)) + (1 << host_bits) - 1;
}

extern int IP_is_valid_id(IP_T ip) {
	return ip == (ip & IP_mask(ip));
}

