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
	while (1) {
		server_listen(&echo);
	}

	/* we should never, ever, ever get here */
	exit(1);
}

/* echo the input to output */
void echo(int fd) {
	/* the line buffer and line string */
	char buffer[BUFSIZE];
	char *line = NULL;
	
	/* read in one line, dyanically allocating the space */
	while(read(fd, buffer, BUFSIZE) != 0) {
		printf("%s", buffer);
		write(fd, buffer, strlen(buffer));
	}
	
}
