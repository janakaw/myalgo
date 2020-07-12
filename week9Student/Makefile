# Makefile for binary heap data structures
#Udaya September 2011

HDRS = pq.h smalloc.h misc.h dump.h

SCRS = heap.c htest.c smalloc.c
OBJS = heap.o htest.o smalloc.o

CC	= gnuc
CFLAGS	= -g -O0 

all:	heap

heap:	$(OBJS)
	$(CC) $(CFLAGS) -o heap $(OBJS)
clean:
	/bin/rm -f heap $(OBJS) 
