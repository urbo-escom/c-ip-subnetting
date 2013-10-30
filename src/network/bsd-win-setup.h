#ifndef BSD_WIN_SOCK_SETUP_H_INCLUDED
#define BSD_WIN_SOCK_SETUP_H_INCLUDED

#include "bsd-win-sock-types.h"
#define T Socket_T

extern int Socket_set_hints(T* sock);
extern int Socket_startup(void);

#endif

