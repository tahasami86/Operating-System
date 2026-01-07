# $@ = target file
# $< = first dependency
# $^ = all dependencies

CC = i386-elf-gcc
LD = i386-elf-ld
ASM = nasm
QEMU = qemu-system-i386
GDB = i386-elf-gdb

CFLAGS  = -ffreestanding -m32 -O0 -Wall -g -gdwarf-4
LDFLAGS = -Ttext 0x1000 --oformat binary
ASMFLAGS= -f bin

C_SRC = $(wildcard kernel/*.c drivers/*.c cpu/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h)
#ASM_SRC = kernel_entry.asm
OBJ = $(C_SRC:.c=.o cpu/interrupt.o) 

# ========== TARGETS ==========
all : run

os-image.bin: boot/bootsect.bin kernel.bin
	cat $^ > $@

kernel.bin : boot/kernel_entry.o $(OBJ)
	$(LD) -o $@ $(LDFLAGS)  $^

# Used for debugging purposes
kernel.elf: boot/kernel_entry.o ${OBJ}
	$(CC) -g -gdwarf-4 -nostdlib -Wl,-Ttext,0x1000 -o $@ $^

bootsect.bin : boot/bootsect.asm
	$(ASM) -o $@ $(ASMFLAGS)  $<


run: os-image.bin
	$(QEMU) -fda $<

# Open the connection to qemu and load our kernel-object file with symbols
debug: os-image.bin kernel.elf
	$(QEMU) -s -fda os-image.bin & 
	$(GDB) -ex "target remote localhost:1234" -ex "file kernel.elf"


%.o : %.asm
	$(ASM) $< $(ASMFLAGS) -f elf -o $@

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

%.bin : %.asm
	$(ASM) -o $@ $(ASMFLAGS)  $<




clean:
	rm -f *.o *.bin *.dis *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o