# Makefile for basic data structures
# awirth
# aug 09


all: testera testerl testerb # btest

btest: Makefile record.o btest.o array.o smalloc.o
	$(CC) $(CFLAGS) -o btest record.o btest.o array.o smalloc.o

testerb: main.o bst.o Makefile smalloc.o #record.o
	$(CC) $(CFLAGS) -o testerb main.o bst.o smalloc.o #record.o

testera: main.o array.o Makefile smalloc.o #record.o
	$(CC) $(CFLAGS) -o testera main.o array.o smalloc.o #record.o

testerl: main.o linked.o Makefile smalloc.o #record.o
	$(CC) $(CFLAGS) -o testerl main.o linked.o smalloc.o # record.o

array.c: smalloc.h record.h data.h Makefile


clean:
	/bin/rm -f $(OBJ) btest testerb testera testerl

OBJ = record.o btest.o array.o linked.o bst.o smalloc.o main.o
CC=gnuc
CFLAGS= -DSORT -g -O0 #-DORDERED
# useful for debugging
