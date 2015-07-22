#Makefile for system with GNU tools
CC = gcc
IFALGS = -idirafter dummyinc
CFLAGS = -O2 -Wall -W -Wshadow


LIBS = 
LINK = 

OBJS = 


.c.0:

v4l2_capture: $(OBJS)
	$(CC)
