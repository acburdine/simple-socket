# Makefile for a simple echo server
# modeled by Nathanael A. Smith after Dr. Vail's Makefile
# also modeled after an example at http://mrbook.org/blog/tutorials/make


# our C compiler
CC=gcc
# the C compiler flags
CFLAGS=-c -Wall

TESTS_DIR = tests

.PHONY: tests

all: sockets tests

sockets: socket.o 

socket.o: socket.c socket.h
	$(CC) $(CFLAGS) socket.c

tests:
	$(MAKE) -C $(TESTS_DIR)
