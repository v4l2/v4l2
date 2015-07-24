#Makefile for system with GNU tools
CC = gcc
IFALGS = -idirafter dummyinc
CFLAGS = -O2 -Wall -W -Wshadow


LIBS = `sh mk_out_path.sh` 
LINK = 

OBJS = capture.o 


.c.o:
	$(CC) -c $*.c $(CFLAGS) $(IFLAGS)

v4l2_capture: $(OBJS)
	$(CC) -o v4l2_capture $(OBJS) 
	$(LIBS)

clean:
	rm -rf out
