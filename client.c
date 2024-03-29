/****************************************************************************
 *		   client.c  => client socket abstraction         	    *
 *                                                                          *
 * Borrowed from example at http://www.linuxhowtos.org/C_C++/socket.htm     *
 *                                                                          *
 * Assignment: Lab 10 - IPC sockets                                         *
 * Author: Nathanael Smith and Austin Burdine                               *
 * Computer: W002-13 and Macbook                                            *
 *                                                                          *
 ****************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

/* printf an error message and exits */
void printError(const char *msg) {
    perror(msg);
    exit(1);
}

/* handles the client setup */
int client_setup(char *host, int port) {
    int serverFd;
    struct sockaddr_in serverAddr;
    struct hostent *server;

    serverFd = socket(AF_INET, SOCK_STREAM, 0);

    if (serverFd < 0) {
        printError("Error on socket open");
    }

    /* resolv the host to a server struct */
    server = gethostbyname(host);

    if (server == NULL) {
        printError("No such host");
    }

    memset((char *) &serverAddr, 0, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    strcpy((char *) &serverAddr.sin_addr.s_addr, (char *) server->h_addr);

    /* try to connect to the server */
    if (connect(serverFd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        printError("Error connecting");
    }

    return serverFd;
}
