# Makefile for a simple echo server
# modeled by Nathanael A. Smith/Austin Burdine after Dr. Vail's Makefile
# also modeled after an example at http://mrbook.org/blog/tutorials/make


# our C compiler
CC=gcc
# the C compiler flags
CFLAGS=-c -Wall

TESTS_DIR = tests

.PHONY: tests

all: server.o client.o tests

server.o: server.c server.h
    $(CC) $(CFLAGS) server.c

client.o: client.c client.h
    $(CC) $(CFLAGS) client.c


tests:
    $(MAKE) -C $(TESTS_DIR)

clean:
    rm *.o 
    $(MAKE) -C $(TESTS_DIR) clean
