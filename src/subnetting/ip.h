#ifndef IP_H_INCLUDED 
#define IP_H_INCLUDED

#include <stdarg.h>

typedef unsigned long int IP_T;

extern int IP_host_bits(IP_T ip);

extern char IP_class(IP_T ip);

extern IP_T IP_mask(IP_T ip);

extern IP_T IP_broadcast(IP_T ip);

extern int IP_is_valid_id(IP_T ip);

extern char* IP_strerror(void);

extern void IP_set_strerror(const char* format, ...);

#endif

