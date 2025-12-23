;receive data in BX register

print:
    pusha

; while (string[i] != 0) { print string[i]; i++ }
start:
    mov al, [bx]
    cmp al, 0
    je end 

    mov ah,0x0E
    int 0x10

    add bx,1
    jmp start


end:
    popa
    ret

print_newline:
    pusha

    mov ah,0x0E
    mov al,0x0A ; newline char
    int 0x10
    mov al,0x0D ; carriage return
    int 0x10

    popa
    ret
