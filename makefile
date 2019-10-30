CC=gcc
CFLAGS=-Wall -ansi -pedantic
DEP = text.h

all: binary name title principals main common
	$(CC) $(CFLAGS) -o a3 main.o binary.o common.o name.o principals.o title.o

main: main.c binary.h common.h title.h principals.h name.h
	$(CC) $(CFLAGS) -c main.c -o main.o

binary: binary.c binary.h common.h
	$(CC) $(CFLAGS) -c binary.c -o binary.o

common: common.c common.h
	$(CC) $(CFLAGS) -c common.c -o common.o

name: name.c name.h binary.h common.h
	$(CC) $(CFLAGS) -c name.c -o name.o

principals: principals.c principals.h binary.h common.h
	$(CC) $(CFLAGS) -c principals.c -o principals.o

title: title.c title.h binary.h common.h
	$(CC) $(CFLAGS) -c title.c -o title.o

clean:
	rm bin/*