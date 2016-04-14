/****************************************************************************
 *		    socket.c => Socket handling for C programs	            *
 *                                                                          *
 * Assignment: Lab 10 - IPC sockets                                         *
 * Author: Nathanael Smith and Austin Burdine                               *
 * Computer: W002-13 and Macbook                                            *
 *                                                                          *
 ****************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int serverFd;

void printError(const char *msg) {
    perror(msg);
    exit(1);
}

int socket_setup(int port) {
    struct sockaddr_in serverAddr;

    serverFd = socket(AF_INET, SOCK_STREAM, 0);

    if (serverFd < 0) {
        printError("Error on socket open");
    }

    memset((char *) &serverAddr, 0, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);
    
    if (bind(serverFd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        printError("Error binding to port");
    }

    listen(serverFd, 5);

    return serverFd;
}

void socket_listen(void (*fn)(int)) {
    int clientFd;
    socklen_t clientLen;
    struct sockaddr_in clientAddr;
    struct sockaddr* clientAddress;

    clientAddress = (struct sockaddr*) &clientAddr;
    clientLen = sizeof (clientAddr);    

    while(1) {
        clientFd = accept(serverFd, clientAddress, &clientLen);

        if (fork() == 0) {
            fn(clientFd);
            close(clientFd);
            exit(0);
        } else {
            close(clientFd);
        }
    }
}
