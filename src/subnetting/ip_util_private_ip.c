#include "ip.h"
#include "ip_util.h"
#include "debug.h"

extern IP_T IP_private_ip(int host_bits, int id) {
	IP_T ip = -1L;
	char address[65];

	/* According to http://tools.ietf.org/html/rfc1918#page-4 */
	switch(host_bits) {
		case 24:
			sprintf(address, "10.0.0.0");
			break;
		case 16:
			id = (id % 16) + 16;
			sprintf(address, "172.%d.0.0", id);
			break;
		case 8:
			id = id % 256;
			sprintf(address, "192.168.%d.0", id);
			break;
		default:
			IP_set_strerror("Unkown class for %d host bits",
			                host_bits);
			log_warn("Unkown class for %d host bits",
			         host_bits);
			return -1L;
			break;
	}

	IP_dot_decimal_to_ip(address, &ip);

	return ip;
}

