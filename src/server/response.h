#ifndef RESPONSE_H_INCLUDED
#define RESPONSE_H_INCLUDED

#include "ip.h"
#include "ip_util.h"
#include "subnet-calc.h"

extern char* info_by_ip_and_hosts(const char* request);
extern char* info_by_ip_and_hosts_per_subnet(const char* request);
extern char* info_by_ip_and_subnets(const char* request);

extern char* info_by_hosts(const char* request);
extern char* info_by_hosts_per_subnet(const char* request);
extern char* info_by_subnets(const char* request);

extern char* subnetting_by_ip_and_hosts(const char* request);
extern char* subnetting_by_ip_and_hosts_per_subnet(const char* request);
extern char* subnetting_by_ip_and_subnets(const char* request);

extern char* subnetting_by_hosts(const char* request);
extern char* subnetting_by_hosts_per_subnet(const char* request);
extern char* subnetting_by_subnets(const char* request);

#endif

