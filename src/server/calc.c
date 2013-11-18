#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "init.h"
#include "exchange.h"
#include "response.h"
#include "request-option-code.h"

extern int calc(const char* request, char* response, int size) {
#define dispatch(s) snprintf(response, size, "%s", s); break
	switch(request_option_code(request)) {
	case INFO_BY_IP_AND_HOSTS:
		dispatch(info_by_ip_and_hosts(request));
	case INFO_BY_IP_AND_HOSTS_PER_SUBNET:
		dispatch(info_by_ip_and_hosts_per_subnet(request));
	case INFO_BY_IP_AND_SUBNETS:
		dispatch(info_by_ip_and_subnets(request));
	case INFO_BY_HOSTS:
		dispatch(info_by_hosts(request));
	case INFO_BY_HOSTS_PER_SUBNET:
		dispatch(info_by_hosts_per_subnet(request));
	case INFO_BY_SUBNETS:
		dispatch(info_by_subnets(request));
	case SUBNETTING_BY_IP_AND_HOSTS:
		dispatch(subnetting_by_ip_and_hosts(request));
	case SUBNETTING_BY_IP_AND_HOSTS_PER_SUBNET:
		dispatch(subnetting_by_ip_and_hosts_per_subnet(request));
	case SUBNETTING_BY_IP_AND_SUBNETS:
		dispatch(subnetting_by_ip_and_subnets(request));
	case SUBNETTING_BY_HOSTS:
		dispatch(subnetting_by_hosts(request));
	case SUBNETTING_BY_HOSTS_PER_SUBNET:
		dispatch(subnetting_by_hosts_per_subnet(request));
	case SUBNETTING_BY_SUBNETS:
		dispatch(subnetting_by_subnets(request));

	case REQUEST_FAILED:
		dispatch("Request parsing failed");
	case UNKNOWN_REQUEST_TYPE:
		dispatch("Unkown request type");
	case SHUTDOWN:
		return 3 + 1*printf("Server shutdown NOW\n");
	default:
		dispatch("This shouldn't happen at all!");
	}
	return 0;
}

