#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "bsd-win-sock.h"
#include "bsd-win-sock-types.h"

static int error_code = 0;
static char str_err[2049];
static void set_strerror(void);
static void reset_strerror(void);

extern void Socket_set_errno(int error) {
	error_code = error;
	set_strerror();
}

extern void Socket_reset_errno(void) {
	error_code = 0;
	reset_strerror();
}

extern int Socket_errno(void) {
	return error_code;
}

extern char* Socket_strerror(void) {
	return str_err;
}

static void set_strerror(void) {
#ifdef __linux
	strcpy(str_err, strerror(errno));
#elif _WIN32
	LPTSTR Error = 0;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, (DWORD)WSAGetLastError(),
		0, (LPTSTR)&Error, 0, NULL);
	strcpy(str_err, Error);
	LocalFree(Error);
#endif
}

static void reset_strerror(void) {
	str_err[0] = '\0';
}

