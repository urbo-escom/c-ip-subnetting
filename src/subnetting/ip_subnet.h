#ifndef IP_SUBNET_H_INCLUDED 
#define IP_SUBNET_H_INCLUDED

#include "ip.h"

typedef unsigned long int Subnet;

extern IP_T Subnet_subnet_id(
		IP_T ip, int subnet_bits, Subnet subnet_number);

extern IP_T Subnet_broadcast(
		IP_T ip, int subnet_bits, Subnet subnet_number);

extern IP_T Subnet_host_start(
		IP_T ip, int subnet_bits, Subnet subnet_number);

extern IP_T Subnet_host_end(
		IP_T ip, int subnet_bits, Subnet subnet_number);

extern IP_T Subnet_mask(
		IP_T ip, int subnet_bits, Subnet subnet_number);

#endif

