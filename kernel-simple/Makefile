# $@ = target file
# $< = first dependency
# $^ = all dependencies

CC = i386-elf-gcc
LD = i386-elf-ld
ASM = nasm
QEMU = qemu-system-i386

CFLAGS  = -ffreestanding -m32 -O0 -Wall
LDFLAGS = -Ttext 0x1000 --oformat binary
ASMFLAGS= -f bin

C_SRC = kernel.c
ASM_SRC = kernel_entry.asm
OBJ = $(ASM_SRC:.asm=.o) $(C_SRC:.c=.o) 

# ========== TARGETS ==========
all : run

kernel.bin : $(OBJ)
	$(LD) -o $@ $(LDFLAGS)  $^


bootsect.bin : bootsect.asm
	$(ASM) -o $@ $(ASMFLAGS)  $<


%.o : %.asm
	$(ASM) $< $(ASMFLAGS) -f elf -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.bin : %.asm
	$(ASM) -o $@ $(ASMFLAGS)  $<

os-image.bin: bootsect.bin kernel.bin
	cat $^ > $@

run: os-image.bin
	$(QEMU) -fda $<

clean:
	rm -f *.o *.bin *.dis