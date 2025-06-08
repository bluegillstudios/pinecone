CC = aarch64-linux-gnu-gcc
AS = aarch64-linux-gnu-as
LD = aarch64-linux-gnu-ld

CFLAGS = -ffreestanding -nostdlib -O2 -Wall -Wextra -I../../include -I../include
ASFLAGS = 
LDFLAGS = -T linker.ld -nostdlib

OBJS = entry.o init.o paging.o

all: kernel.elf kernel.bin

entry.o: entry.S
	$(AS) $(ASFLAGS) entry.S -o entry.o

init.o: init.c
	$(CC) $(CFLAGS) -c init.c -o init.o

paging.o: paging.c
	$(CC) $(CFLAGS) -c paging.c -o paging.o

kernel.elf: $(OBJS) linker.ld
	$(LD) $(LDFLAGS) $(OBJS) -o kernel.elf

kernel.bin: kernel.elf
	objcopy -O binary kernel.elf kernel.bin

clean:
	rm -f *.o kernel.elf kernel.bin
