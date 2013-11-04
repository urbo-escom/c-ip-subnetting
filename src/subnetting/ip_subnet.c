#include "ip_subnet.h"

extern IP_T Subnet_subnet_id(
		IP_T ip, int subnet_bits, Subnet subnet_number) {
	int host_bits = IP_host_bits(ip);
	return	/* IP N000 or NN00 or NNN0 */
		ip +
		/* Subnet N...NS...S00...0, S...S = subnet number */
		(subnet_number << (host_bits - subnet_bits));
}

extern IP_T Subnet_broadcast(
		IP_T ip, int subnet_bits, Subnet subnet_number) {
	int host_bits = IP_host_bits(ip);
	return	ip +
		/**   N...NS..S000...0
		  * + N...N0..1000...0 - 1
		  * = N...NSSSS111...1     */
		((subnet_number + 1L) << (host_bits - subnet_bits)) - 1L;
}

extern IP_T Subnet_host_start(
		IP_T ip, int subnet_bits, Subnet subnet_number) {
	return	Subnet_subnet_id(ip, subnet_bits,
		                   subnet_number) + 1L;
}

extern IP_T Subnet_host_end(
		IP_T ip, int subnet_bits, Subnet subnet_number) {
	return	Subnet_broadcast(ip, subnet_bits,
		                   subnet_number) - 1L;
}

extern IP_T Subnet_mask(
		IP_T ip, int subnet_bits, Subnet subnet_number) {
	int host_bits = IP_host_bits(ip);
	return	/* 111..111 -> 11..1100..00 */
		(-1L) << (host_bits - subnet_bits);
}

