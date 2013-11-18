#ifndef IP_UTIL_H_INCLUDED 
#define IP_UTIL_H_INCLUDED

#include "ip.h"

typedef unsigned long int host_size_t;
typedef unsigned long int subnet_size_t;

/* Returns -1 if it fails */
extern int IP_dot_decimal_to_ip(char* address, IP_T* ip);

/* Returns -1 if it fails */
extern int IP_ip_to_dot_decimal(IP_T ip, char* address);

/** Return the first value of subnet bits that
  * asserts the condition of producing less or equal
  * hosts, host/subnet or subnets, -1 if doesn't exits
  */
extern int IP_subnet_bits_by_total_hosts(
		IP_T ip, host_size_t total_hosts);

extern int IP_subnet_bits_by_hosts_per_subnet(
		IP_T ip, host_size_t hosts_per_subnet);

extern int IP_subnet_bits_by_subnets(
		IP_T ip, subnet_size_t subnets);

/** Returns: Class C host bits if it can handle subnetting
  * if not : Class B host bits if it can handle subnetting
  * if not : Class A host bits if it can handle subnetting
  * if not (and you're unlucky): -1
  */
extern int IP_host_bits_by_total_hosts(host_size_t total_hosts);
extern int IP_host_bits_by_hosts_per_subnet(host_size_t hosts_per_subnet);
extern int IP_host_bits_by_subnets(subnet_size_t subnets);

extern subnet_size_t IP_subnets_size(int subnet_bits);

/** Returns a private IP,
  * IP's are numbered from 0 to the size of private IP's - 1
  * the id is taken as modulo the size of private IP's
  */
extern IP_T IP_private_ip(int host_bits, int id);

#endif

