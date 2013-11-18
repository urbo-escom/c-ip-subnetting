#ifndef SUBNET_CALC_PRIVATE_IP_H_INCLUDED
#define SUBNET_CALC_PRIVATE_IP_H_INCLUDED

#include "ip.h"
#include "ip_subnet.h"
#include "ip_util.h"

/* Private IP's (unknown) (Format: "ip class subnet_bits subnets_size") */
extern char* SubnetCalc_get_info_by_hosts(
		host_size_t hosts, int id);

extern char* SubnetCalc_get_info_by_hosts_per_subnet(
		host_size_t hosts_per_subnet, int id);

extern char* SubnetCalc_get_info_by_subnets(
		subnet_size_t subnets, int id);

/* Private IP's (unknown) ("# Use id broadcast mask host-start host-end") */
extern char* SubnetCalc_subnetting_by_hosts(
		host_size_t hosts, int id, Subnet subnet_number);

extern char* SubnetCalc_subnetting_by_hosts_per_subnet(
		host_size_t hosts_per_subnet, int id, Subnet subnet_number);

extern char* SubnetCalc_subnetting_by_subnets(
		subnet_size_t hosts, int id, Subnet subnet_number);

#endif

