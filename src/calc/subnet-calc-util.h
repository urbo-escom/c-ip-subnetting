#ifndef SUBNET_CALC_UTIL_H_INCLUDED
#define SUBNET_CALC_UTIL_H_INCLUDED

#include "ip.h"
#include "ip_subnet.h"
#include "ip_util.h"

/* (Format: "ip class subnet_bits subnets_size") */ 
extern char* SubnetCalcUtil_get_info(
		IP_T ip, int subnet_bits);

/* (Format: "# Use id broadcast mask host-start host-end") */
extern char* SubnetCalcUtil_subnetting(
		IP_T ip, int subnet_bits, Subnet subnet_number);


#endif

