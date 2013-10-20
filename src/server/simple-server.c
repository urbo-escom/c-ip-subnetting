#include <stdio.h>
#include <stdlib.h>

#ifdef _linux

#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#elif _WIN32

#include <winsock.h>

#define socklen_t int

#define close(s) \
	closesocket(s);\
	WSACleanup();

#endif

#define PORTNUM 2343
 
int main(int argc, char *argv[]) {

    #ifdef _WIN32
    WSADATA wsaData;

    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
       fprintf(stderr,"WSAStartup() failed");
       exit(1);
    }
    #endif

    char msg[] = "Hello client !\n";

    struct sockaddr_in dest; /* socket info about the machine connecting to us */
    struct sockaddr_in serv; /* socket info about our server */
    int mysocket;            /* socket used to listen for incoming connections */
    socklen_t socksize = sizeof(struct sockaddr_in);
 
    memset(&serv, 0, sizeof(serv));           /* zero the struct before filling the fields */
    serv.sin_family = AF_INET;                /* set the type of connection to TCP/IP */
    serv.sin_addr.s_addr = htonl(INADDR_ANY); /* set our address to any interface */
    serv.sin_port = htons(PORTNUM);           /* set the server port number */    
 
    mysocket = socket(AF_INET, SOCK_STREAM, 0);
 
    /* bind serv information to mysocket */
    bind(mysocket, (struct sockaddr *)&serv, sizeof(struct sockaddr));
 
    /* start listening, allowing a queue of up to 1 pending connection */
    listen(mysocket, 1);
    int consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
 
    while(consocket)
    {
        printf("Incoming connection from %s - sending welcome\n", inet_ntoa(dest.sin_addr));
        send(consocket, msg, strlen(msg), 0); 
        consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
    }
 
    close(consocket);
    close(mysocket);
    return EXIT_SUCCESS;
}

