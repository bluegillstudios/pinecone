AS = aarch64-linux-gnu-as
LD = aarch64-linux-gnu-ld
OBJCOPY = aarch64-linux-gnu-objcopy

ASFLAGS = -march=armv8-a
LDFLAGS = -T linker.ld -nostdlib

all: bootloader.bin

bootloader.o: boot.S
	$(AS) $(ASFLAGS) boot.S -o bootloader.o

bootloader.elf: bootloader.o linker.ld
	$(LD) $(LDFLAGS) bootloader.o -o bootloader.elf

bootloader.bin: bootloader.elf
	$(OBJCOPY) -O binary bootloader.elf bootloader.bin

clean:
	rm -f *.o *.elf *.bin
