/****************************************************************************
 *		   socket.h => Header file for the socket functionality     *
 *                                                                          *
 * Assignment: Lab 10 - IPC sockets                                         *
 * Author: Nathanael Smith and Austin Burdine                               *
 * Computer: W002-13 and Macbook                                            *
 *                                                                          *
 ****************************************************************************/

int socket_setup(int port);
void socket_listen(void (*fn)(int));
