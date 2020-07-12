# Makefile for sorting exercise
# udaya
#July2011

HDRS = basicsort.h  

COM_SCRS = basicsorts.c  
COM_OBJS = basicsorts.o 

SORTS_SCRS = basic_main.c 
SORTS_OBJS = basic_main.o

ASORTS_SCRS = adv_main.c  
ASORTS_OBJS = adv_main.o

CC = gnuc 
CFLAGS= -g -O0
all: SORT1 SORT2 

SORT1: $(COM_OBJS) $(SORTS_OBJS)
	$(CC)$(CFLAGS) -o SORT1 $(COM_OBJS) $(SORTS_OBJS)

SORT2: $(COM_OBJS) $(ASORTS_OBJS)
	$(CC)$(CFLAGS) -o SORT2 $(COM_OBJS) $(ASORTS_OBJS)

clean:
	/bin/rm -f SORT1 SORT2 $(COM_OBJS) $(SORTS_OBJS) 
