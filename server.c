/****************************************************************************
 *	     server.c => Server socket handling for C programs	            *
 *                                                                          *
 * Borrowing an example from http://www.linuxhowtos.org/C_C++/socket.htm    *
 *                                                                          *
 * Assignment: Lab 10 - IPC sockets                                         *
 * Author: Nathanael Smith and Austin Burdine                               *
 * Computer: W002-13 and Macbook                                            *
 *                                                                          *
 ****************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* the server's file descriptor */
int serverFd;

/* prints an error message and exits */
void printError(const char *msg) {
    perror(msg);
    exit(1);
}

/* sets up the server's socket given a port number */
/* returns the socket */
int server_setup(int port) {
    struct sockaddr_in serverAddr;

    serverFd = socket(AF_INET, SOCK_STREAM, 0);

    if (serverFd < 0) {
        printError("Error on socket open");
    }

    memset((char *) &serverAddr, 0, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    /* try to connect to the server */
    if (bind(serverFd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        printError("Error binding to port");
    }

    listen(serverFd, 5);

    return serverFd;
}

/* continuously listens for new connections to the server */
/* can handle multiple clients */
/* the function passed as a parameter here will be executed upon forking */
/* this function must take a file descriptor as an argument */
void server_listen(void (*fn)(int)) {
    int clientFd;
    socklen_t clientLen;
    struct sockaddr_in clientAddr;
    struct sockaddr* clientAddress;

    clientAddress = (struct sockaddr*) &clientAddr;
    clientLen = sizeof (clientAddr);    

    /* loop infinitely */
    while(1) {
        clientFd = accept(serverFd, clientAddress, &clientLen);

        /* fork twice to avoid zombie processes */
        /* the grandchild will be inherited by init, which automatically wait()s */
        /* thanks to http://stackoverflow.com/questions/16078985/why-zombie-processes-exist */
        if (fork() == 0) {
            if (fork() == 0) {
                fn(clientFd);
                close(clientFd);
                exit(0);
            }
            close(clientFd);
            exit(0);
        } else {
            wait(NULL);
            close(clientFd);
        }
    }
}
