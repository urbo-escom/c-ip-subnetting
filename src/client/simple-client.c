#include <stdio.h>
#include <stdlib.h>

#ifdef __linux

#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#elif _WIN32

#include <winsock.h>

#define close(s) \
	closesocket(s);\
	WSACleanup();

#endif
 

#define MAXRCVLEN 500
#define PORTNUM 2343
 
int main(int argc, char *argv[]) {

    #ifdef _WIN32
    WSADATA wsaData;

    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
       fprintf(stderr,"WSAStartup() failed");
       exit(1);
    }
    #endif

   char buffer[MAXRCVLEN + 1]; /* +1 so we can add null terminator */
   int len, mysocket;
   struct sockaddr_in dest; 
 
   mysocket = socket(AF_INET, SOCK_STREAM, 0);
 
   memset(&dest, 0, sizeof(dest));                /* zero the struct */
   dest.sin_family = AF_INET;
   dest.sin_addr.s_addr = inet_addr("127.0.0.1"); /* set destination IP number */ 
   dest.sin_port = htons(PORTNUM);                /* set destination port number */
 
   connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr));

   char* request = "Hello server !";
   send(mysocket, request, strlen(request), 0);

   len = recv(mysocket, buffer, MAXRCVLEN, 0);
 
   /* We have to null terminate the received data ourselves */
   buffer[len] = '\0';
 
   printf("Received %s (%d bytes).\n", buffer, len);
 
   close(mysocket);
   return EXIT_SUCCESS;
}

