/****************************************************************************
 *        {echo.c}  => {a simple echo client to test our socket lib}        *
 *                                                                          *
 * Assignment: Lab 10 - IPC sockets                                         *
 * Author: Nathanael Smith and Austin Burdine                               *
 * Computer: W002-13 and Macbook                                            *
 *                                                                          *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "echo.h"
#include "../../client.h"

int main(int argc, char **argv) {

	char *hostname;
	int port;

	if (argc == 1) {
		hostname = "localhost";
		port = 7;
	}
	else if (argc == 2) {
		hostname = argv[1];
		port = 7;
	}
	else {
		hostname = argv[1];
		port = atoi(argv[2]);
	}

	/* configure socket stuff */
	int fd = client_setup(hostname, port);

	char buffer[BUFSIZE];

	/* loop until ctrl-c */
	while (1) {
		printf("> ");
		while (fgets(buffer, BUFSIZE, stdin) != NULL) {
			write(fd, buffer, strlen(buffer) + 1);
			memset(buffer, 0, BUFSIZE);
			while (read(fd, buffer, BUFSIZE) != 0) {
				printf("%s", buffer);
				memset(buffer, 0, BUFSIZE);
				break;
			}
			break;
		}
	}
}
