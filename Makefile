CC=gcc
CFLAGS=-g -pedantic -std=gnu17 -Wall -Werror -Wextra

.PHONY: main

main: main.o main.cpp main.hpp

.PHONY: clean
clean:
	rm -f *.o nyush