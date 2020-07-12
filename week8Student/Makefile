# Makefile for week 8
# awirth
# aug 09
# udaya Sep 11

all: gtestl

gtestl: gtest.o smalloc.o lgraph.o Makefile
	$(CC) $(CFLAGS) -o gtestl gtest.o smalloc.o lgraph.o

clean:
	/bin/rm -f *.o gtestl gtestm

CC=gnuc
CFLAGS=-g -O0
