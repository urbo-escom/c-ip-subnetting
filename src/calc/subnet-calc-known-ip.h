#ifndef SUBNET_CALC_KNOWN_IP_H_INCLUDED
#define SUBNET_CALC_KNOWN_IP_H_INCLUDED

#include "ip.h"
#include "ip_subnet.h"
#include "ip_util.h"

/* Known IP's (Format: "ip class subnet_bits subnets_size") */
extern char* SubnetCalc_get_info_by_ip_and_hosts(
		IP_T ip, host_size_t hosts);

extern char* SubnetCalc_get_info_by_ip_and_hosts_per_subnet(
		IP_T ip, host_size_t hosts_per_subnet);

extern char* SubnetCalc_get_info_by_ip_and_subnets(
		IP_T ip, subnet_size_t subnets);

/* Known IP's (Format: "# Use id broadcast mask host-start host-end") */
extern char* SubnetCalc_subnetting_by_ip_and_hosts(
		IP_T ip, host_size_t hosts, Subnet subnet_number);

extern char* SubnetCalc_subnetting_by_ip_and_hosts_per_subnet(
		IP_T ip, host_size_t hosts_per_subnet, Subnet subnet_number);

extern char* SubnetCalc_subnetting_by_ip_and_subnets(
		IP_T ip, subnet_size_t subnets, Subnet subnet_number);

#endif

