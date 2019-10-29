CC=gcc
CFLAGS=-Wall -ansi -pedantic -Iincludes 
DEP = text.h

all: text

binary: binary.c binary.h common.h
	$(CC) $(CFLAGS) binary.c -o binary

name: name.c name.h binary.h common.h
	$(CC) $(CFLAGS) name.c -o name

title: title.c title.h binary.h common.h
	$(CC) $(CFLAGS) title.c -o title

principals: principals.c principals.h binary.h common.h
	$(CC) $(CFLAGS) principals.c -o principals

a3: main.c binary.h common.h title.h principals.h name.h
	$(CC) $(CLAGS) main.c -o main

clean:
	rm binary.o name.o title.o principals.o a3.o