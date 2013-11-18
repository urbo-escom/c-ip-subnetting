#ifndef BSD_WIN_SOCK_H_INCLUDED
#define BSD_WIN_SOCK_H_INCLUDED

#define T Socket_T
typedef struct T T;

extern T*   Socket_new(const char* address, const char* portnum);
extern void Socket_free(T** socket);

/** General workflow for a server:
  * create -> bind -> accept -> send/recv -> free
  * General workflow for a client:
  * create -> connect -> send/recv -> free
  */

extern int  Socket_bind(T* socket);
extern int  Socket_listen(T* socket, int connections);
extern int  Socket_accept(T* socket);
extern int  Socket_connect(T* socket);
extern int  Socket_timeout(T* socket, int seconds);

extern char* Socket_get_ip(T* socket);
extern char* Socket_get_port(T* socket);

extern int  Socket_send(T* socket, const char* msg, int msg_len);
extern int  Socket_receive(T* socket, char* msg, int msg_len);

/* For error handling */
extern char* Socket_strerror(void);
extern int   Socket_errno(void);
extern void  Socket_set_errno(int error);
extern void  Socket_reset_errno(void);

#undef T
#endif

