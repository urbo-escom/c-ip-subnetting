#include <stdio.h>
#include "ip.h"
#include "debug.h"

static IP_T octect(IP_T ip, int i) {
	/* 00 00 00 11 */
	IP_T aux_mask = (1UL << 8) - 1UL;
	IP_T mask_me_masker = aux_mask << (i*8);

	return (ip & mask_me_masker) >> (i*8);
}

extern int IP_ip_to_dot_decimal(IP_T ip, char* address) {
	log_debug("Adress to be written: %lx", ip);
	sprintf(address, "%lu.%lu.%lu.%lu",
	        octect(ip, 3),  /* X000 */
		octect(ip, 2),  /* 0X00 */
		octect(ip, 1),  /* 00X0 */
		octect(ip, 0)); /* 000X */

	log_debug("Address written: %s", address);
	return 0;
}

