#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "request-option-code.h"

#define equal(s,t) (strcmp((s), (t)) == 0)

extern int request_option_code(const char* request) {
	char s[8193];
	memset(s, 0, sizeof(s));

	if (sscanf(request, "%s", s) != 1)
		return REQUEST_FAILED;
	if (equal(s, "info_by_ip_and_hosts"))
		return INFO_BY_IP_AND_HOSTS;
	if (equal(s, "info_by_ip_and_hosts_per_subnet"))
		return INFO_BY_IP_AND_HOSTS_PER_SUBNET;
	if (equal(s, "info_by_ip_and_subnets"))
		return INFO_BY_IP_AND_SUBNETS;

	if (equal(s, "info_by_hosts"))
		return INFO_BY_HOSTS;
	if (equal(s, "info_by_hosts_per_subnet"))
		return INFO_BY_HOSTS_PER_SUBNET;
	if (equal(s, "info_by_subnets"))
		return INFO_BY_SUBNETS;

	if (equal(s, "subnetting_by_ip_and_hosts"))
		return SUBNETTING_BY_IP_AND_HOSTS;
	if (equal(s, "subnetting_by_ip_and_hosts_per_subnet"))
		return SUBNETTING_BY_IP_AND_HOSTS_PER_SUBNET;
	if (equal(s, "subnetting_by_ip_and_subnets"))
		return SUBNETTING_BY_IP_AND_SUBNETS;

	if (equal(s, "subnetting_by_hosts"))
		return SUBNETTING_BY_HOSTS;
	if (equal(s, "subnetting_by_hosts_per_subnet"))
		return SUBNETTING_BY_HOSTS_PER_SUBNET;
	if (equal(s, "subnetting_by_subnets"))
		return SUBNETTING_BY_SUBNETS;

	if (equal(s, "shutdown") || equal(s, "shutdown\r\n"))
		return SHUTDOWN;

	return UNKNOWN_REQUEST_TYPE;
}

