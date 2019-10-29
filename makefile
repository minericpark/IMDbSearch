CC=gcc
CFLAGS=-Wall -ansi -pedantic -Iincludes 
DEP = text.h

all: text

text: text.c text.h
	$(CC) $(CFLAGS) text.c -o text

clean:
	rm text.o