# Makefile for stack exercise
# udaya
#July2011

HDRS = stack.h queue.h 

COM_SCRS = stack.c queue.c 
COM_OBJS = stack.o queue.o

STK_SCRS = stack_main.c 
STK_OBJS = stack_main.o

Que_SCRS = queue_main.c 
Que_OBJS = queue_main.o

POSTF_SCRS = postfix_main.c 
POSTF_OBJS = postfix_main.o

CC = gnuc 
CFLAGS= -g -O0
all: STAK Que POSTF 

STAK: $(COM_OBJS) $(STK_OBJS)
	$(CC)$(CFLAGS) -o STAK $(COM_OBJS) $(STK_OBJS)

Que: $(COM_OBJS) $(Que_OBJS)
	$(CC)$(CFLAGS) -o Que $(COM_OBJS) $(Que_OBJS)

POSTF: $(COM_OBJS) $(POSTF_OBJS)
	$(CC)$(CFLAGS) -o POSTF $(COM_OBJS) $(POSTF_OBJS)

clean:
	/bin/rm -f STAK $(COM_OBJS) $(STK_OBJS) $(Que_OBJS) $(POSTF_OBJS)

