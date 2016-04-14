# Makefile for a simple echo server
# modeled by Nathanael A. Smith/Austin Burdine after Dr. Vail's Makefile
# also modeled after an example at http://mrbook.org/blog/tutorials/make


# our C compiler
CC=gcc
# the C compiler flags
CFLAGS=-c -Wall

ECHO_DIR = echo

.PHONY: echo
.PHONY: clean

echo: 
	$(MAKE) -C $(ECHO_DIR)

clean: 
	$(MAKE) -C $(ECHO_DIR) clean
