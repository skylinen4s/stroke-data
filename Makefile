CC = gcc
CFLAGS = -O0 -g -Wall -Wextra -std=c99 -pedantic-errors

all: test

.PHONY: test
test: stroke.c parson.c
	$(CC) $(CFLAGS) -o stroke stroke.c parson.c

clean:
	rm -f test *.o
