[org 0x7c00]

mov bp,0x800 ; Set up stack segment away from boot sector
mov sp,bp

mov bx,0x9000 ; Set up data segment 0000:9000 → physical 0x9000 Where we will load the data


mov dh,0x02 ; Number of sectors to read

call disk_load ; Call disk load function to read sectors from disk

mov dx,[0x9000] ; Set DX to point to loaded data, retrieve the first loaded word 0xdada from first sector i:e(2nd sector overall)
call print_hex ; Print the loaded word in hex

call print_newline ; Print a newline

mov dx,[0x9000 +512] ;;retrieve the word loaded from second sector i:e(3rd sector overall) 0xface
call print_hex ; Print the loaded word in hex

jmp $


%include  "../boot-function-strings/boot_sect_hex_print.asm"
%include  "../boot-function-strings/boot_sect_print.asm"
%include "boot_sect_disk.asm"

times 510-($-$$) db 0 ; Pad the rest of the boot sector with zeros
dw 0xAA55 ; Boot sector signature

times 256 dw 0xdada ; Dummy data to be loaded from disk from sector 2 = 512 bytes
times 256 dw 0xface  ; Dummy data to be loaded from disk from sector 3 = 512 bytes