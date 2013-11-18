#include "bsd-win-sock.h"
#include "bsd-win-sock-types.h"
#include "bsd-win-setup.h"
#include "debug.h"

extern int Socket_startup() {
#ifdef _WIN32
	WSADATA wsaData;
	log_debug("Initializing WSA");
	int startup = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (startup != 0) {
		Socket_set_errno(SOCKET_ERR_WSA_STARTUP);
		log_err("WSAStartup failed: %s",
		        Socket_strerror());
		return -1;
	}
#endif
	log_debug("Socket startup succeded");
	return 0;
}

