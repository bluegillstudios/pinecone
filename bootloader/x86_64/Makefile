NASM = nasm
LD = ld
OBJCOPY = objcopy

NASMFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T linker.ld --oformat binary

BOOTLOADER = bootloader.bin
OBJ = boot.o

all: $(BOOTLOADER)

boot.o: BOOT.ASM
	$(NASM) $(NASMFLAGS) BOOT.ASM -o boot.o

$(BOOTLOADER): boot.o linker.ld
	$(LD) $(LDFLAGS) boot.o -o $(BOOTLOADER)

clean:
	rm -f *.o $(BOOTLOADER)
