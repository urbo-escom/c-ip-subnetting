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
	if (equal(s, "info-by-ip-and-hosts"))
		return INFO_BY_IP_AND_HOSTS;
	if (equal(s, "info-by-ip-and-hosts-per-subnet"))
		return INFO_BY_IP_AND_HOSTS_PER_SUBNET;
	if (equal(s, "info-by-ip-and-subnets"))
		return INFO_BY_IP_AND_SUBNETS;

	if (equal(s, "info-by-hosts"))
		return INFO_BY_HOSTS;
	if (equal(s, "info-by-hosts-per-subnet"))
		return INFO_BY_HOSTS_PER_SUBNET;
	if (equal(s, "info-by-subnets"))
		return INFO_BY_SUBNETS;

	if (equal(s, "subnetting-by-ip-and-hosts"))
		return SUBNETTING_BY_IP_AND_HOSTS;
	if (equal(s, "subnetting-by-ip-and-hosts-per-subnet"))
		return SUBNETTING_BY_IP_AND_HOSTS_PER_SUBNET;
	if (equal(s, "subnetting-by-ip-and-subnets"))
		return SUBNETTING_BY_IP_AND_SUBNETS;

	if (equal(s, "subnetting-by-hosts"))
		return SUBNETTING_BY_HOSTS;
	if (equal(s, "subnetting-by-hosts-per-subnet"))
		return SUBNETTING_BY_HOSTS_PER_SUBNET;
	if (equal(s, "subnetting-by-subnets"))
		return SUBNETTING_BY_SUBNETS;

	if (equal(s, "shutdown") || equal(s, "shutdown\r\n"))
		return SHUTDOWN;

	return UNKNOWN_REQUEST_TYPE;
}

