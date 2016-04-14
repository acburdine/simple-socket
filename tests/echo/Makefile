# Makefile for a simple echo server
# modeled by Nathanael A. Smith/Austin Burdine after Dr. Vail's Makefile
# also modeled after an example at http://mrbook.org/blog/tutorials/make


# our C compiler
CC=gcc
# the C compiler flags
CFLAGS=-c -Wall

echo: echo-client echod

echo-client: echo.o
	$(CC) -o echo echo.o

echod: echod.o
	$(CC) -o echod echod.o

echo.o: echo.c echo.h
	$(CC) $(CFLAGS) echo.c ../../socket.c

echod.o: echod.c echod.h
	$(CC) $(CFLAGS) echod.c ../../socket.c

clean: 
	rm *.o echo echod
