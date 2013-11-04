#include <stdio.h>
#include "ip.h"
#include "debug.h"

extern int IP_dot_decimal_to_ip(char* address, IP_T* ip) {
	unsigned int octect[4];
	int scanned;

	log_debug("Parsing: %s", address);
	scanned = sscanf(address, "%d%*[.]%d%*[.]%d%*[.]%d",
	                 &octect[0], &octect[1], &octect[2], &octect[3]);
	if (scanned != 4) {
		IP_set_strerror("Incorrect decimal format ip '%s'", address);
		log_warn("Incorrect decimal format ip '%s'", address);
		return -1;
	}

	if (223 < octect[0]) {
		IP_set_strerror("Unknown class: %s", address);
		log_warn("Unknown class: %s", address);
		return -1;
	}
	*ip = 0UL;
	int i;
	for(i = 0; i < 4; i++) {
		*ip = (*ip) << 8;
		if (0 <= octect[i] && octect[i] <= 255) {
			log_debug("Octect[%d] = %d", i, octect[i]);
			*ip += octect[i];
		} else {
			IP_set_strerror(
				"Octect not in interval: %d", octect[i]);
			log_warn("Octect not in interval: %d", octect[i]);
			return -1;
		}
	}

	log_debug("Parsed IP:%lx", *ip);
	return 0;
}

