#include <stdlib.h>
#include "bsd-win-sock.h"
#include "bsd-win-sock-types.h"
#include "debug.h"

#define T Socket_T

static int Socket_peername(T* sock) {
	socklen_t len;
	struct sockaddr_storage addr;

	len = sizeof addr;

	log_debug("Getting peer name");
	if (getpeername(sock->sockfd_dest,
	                (struct sockaddr*)&(addr),
	                &len) == SOCKET_ERROR) {
		Socket_set_errno(SOCKET_ERR_GET_PEER_NAME);
		log_err("Get peer name failed: %s", Socket_strerror());
		return -1;
	}

	if (addr.ss_family != AF_INET) {
		log_err("No IPv4 address");
		return -1;
	}

	struct sockaddr_in *s = (struct sockaddr_in *)&addr;
	sprintf(sock->peer_ip, "%s", inet_ntoa(s->sin_addr));
	sprintf(sock->peer_port, "%d", ntohs(s->sin_port));
	return 0;
}

extern char* Socket_get_ip(T* sock) {
	Socket_peername(sock);
	return sock->peer_ip;
}

extern char* Socket_get_port(T* sock) {
	Socket_peername(sock);
	return sock->peer_port;
}

