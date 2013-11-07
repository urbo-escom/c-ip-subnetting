#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "subnet-calc-util.h"

static char s[1025];

/* (Format: "# Use id broadcast mask host-start host-end") */
extern char* SubnetCalcUtil_subnetting(
		IP_T ip, int subnet_bits, Subnet subnet_number) {
	if (!IP_is_valid_id(ip)) {
		sprintf(s, "error Invalid ID for %lx", ip);
		return s;
	} else if (!(1 < subnet_bits && subnet_bits < IP_host_bits(ip) - 1)) {
		sprintf(s, "error "
			"Inadequate subnet bits (%d bits) for %lx",
			subnet_bits, ip);
		return s;
	}

	IP_T net_id = Subnet_subnet_id(ip, subnet_bits, subnet_number);
	IP_T broadcast = Subnet_broadcast(ip, subnet_bits, subnet_number);
	IP_T mask = Subnet_mask(ip, subnet_bits, subnet_number);
	IP_T host_start = Subnet_host_start(ip, subnet_bits, subnet_number);
	IP_T host_end = Subnet_host_end(ip, subnet_bits, subnet_number);

	char aux[65];
	sprintf(s, "%lu ", subnet_number);

	sprintf(aux, "%s", Subnet_is_used(ip, subnet_bits, subnet_number)?
		"yes":"no");
	strcat(s, aux);

#define append_ip(ip) do{\
	IP_ip_to_dot_decimal(ip, aux);\
	strcat(s, aux);\
	sprintf(aux, " ");\
	strcat(s, aux); } while(0)

	append_ip(net_id);
	append_ip(broadcast);
	append_ip(mask);
	append_ip(host_start);
	append_ip(host_end);

	return s;
}

