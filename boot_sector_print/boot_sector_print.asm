mov ah, 0x0E ; BIOS TTY output function
mov al, 'H'  ; Character to print
int 0x10     ; Call BIOS interrupt to print character
mov al, 'E'  ; Character to print'
int 0x10
mov al, 'L'  ; Character to print
int 0x10
int 0x10     ; Print 'L' again
mov al, 'O'
int 0x10

jmp $        ; Infinite loop to halt the program

; Boot sector padding and signature
times 510-($-$$) db 0 ; Fill the rest of the boot sector with zeros
dw 0xAA55                ; Boot sector signature