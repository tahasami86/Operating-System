[org 0x7c00]

mov bx,HELLO
call print 

call print_newline

mov bx,GOODBYE
call print

call print_newline

mov dx,0x1789 ; example number to print in hex
call print_hex

jmp $ ; Infinite loop to halt the CPU

%include "boot_sect_print.asm"
%include "boot_sect_hex_print.asm"

HELLO:
    db 'Hello, World!',0

GOODBYE:
    db 'Goodbye, World!',0

times 510-($-$$) db 0
dw 0xAA55