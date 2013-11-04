#include <stdio.h>
#include <stdarg.h>

#include "ip.h"

static char error[65*1024];

extern char* IP_strerror(void) {
	return error;
}

extern void IP_set_strerror(const char* format, ...) {
	va_list arglist;
	va_start(arglist, format);
	vsprintf(error, format, arglist);
	va_end(arglist);
	return;
}

