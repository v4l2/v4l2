#Makefile for system with GNU tools
#CC = arm-linux-gcc
#IFALGS = -idirafter dummyinc
#CFLAGS = -O2 -c -Wall -W -Wshadow -o

#PATH = /usr/include
LIBS = `sh mk_out_path.sh` 
LINK = 

OBJS = capture.o socket.o 

capture.bin: $(OBJS)
#	arm-linux-ld -Ttext 0x30000000 -o cap_elf $^
#	arm-linux-objcopy -O binary -S cap_elf $@
#	arm-linux-objdump -D -m arm cap_elf > cap.dis
	gcc -Wunused-result -o v4l2_capture $^ -lpthread
	$(LIBS)

%.o:%.c
	gcc -Wall -O2 -c -o $@ $< 

clean:
	rm -rf out
