/****************************************************************************
 *         {echod.c}  => {} simple echo server to test our socket lib       *
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

#include "../../server.h"
#include "echod.h"

/* let's do this */
int main() {
	/* set up a server socket */
	server_setup(23457);

	/* loop until ctrl-c */
	server_listen(&echo);

	/* we should never, ever, ever get here */
	exit(1);
}

/* echo the input to output */
void echo(int fd) {
	char buffer[BUFSIZE];
	
	while (read(fd, buffer, BUFSIZE)) {
		printf("%s\n", buffer);
		write(fd, buffer, strlen(buffer));
		memset(buffer, 0, BUFSIZE);
	}
}
