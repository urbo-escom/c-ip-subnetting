#ifndef EXCHANGE_H_INCLUDED
#define EXCHANGE_H_INCLUDED

#include "bsd-win-sock.h"

#define Server_T T
typedef Socket_T T;

extern T*   Server_create(const char* port);
extern void Server_close(T** server);
/* Response must return a non zero value to stop listening */
extern int  Server_init(
		T* server,
		int (*response)(
			const char* request, char* response, int size));

#undef T
#define Client_T T
typedef Socket_T T;

extern T*   Client_create(const char* ip, const char* p);
extern void Client_close(T** client);
/* Request must return a non zero value to stop listening */
extern int  Client_init(
		T* client,
		int (*request)(
			char* request, const char* response, int size));

#endif

