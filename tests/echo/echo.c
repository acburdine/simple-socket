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


	char buffer[BUFSIZE];

	/* loop until ctrl-c */
	while (1) {
		printf("> ");

		/* the line array */
		char *line = NULL;
		
		/* get one line */
		while (fgets(buffer, BUFSIZE, stdin) != NULL) {
			/* append line to line array */
			if (line == NULL) {
				line = (char *)malloc(strlen(buffer) + 1);
				*line = '\0';
			}
			else {
				line = (char *)realloc(line, strlen(line) + strlen(buffer) + 1);
			}

			line = strcat(line, buffer);

			/* see if line is done */
			if (strlen(buffer) + 1 <  BUFSIZE ||
					(strlen(buffer) + 1 == BUFSIZE &&
					  buffer[BUFSIZE-2] == '\n')) {
				/* we're done with this line */
				enqueue(line);
				line = NULL;
			}
		}
		
		/* write the line to the server */
		write(fd, line, strlen(line) + 1);

		while (read(fd, buffer, BUFSIZE) != 0) {
			printf("%s", buffer);
		}
	}
}
