mov ah,0x0e ; tty output

mov al, the_secret
int 0x10 ; Will print the wrong character

mov bx,0x7c0
mov ds,bx
mov al, [the_secret]
int 0x10 ; Will print the correct character

mov al,[es:the_secret]
int 0x10  ; Will print the wrong character  again 'es' currently 0x000?

;Fixing ES:
mov bx,0x7c0
mov es,bx
mov al,[es:the_secret]
int 0x10 ; Will print the correct character "X"

jmp $


the_secret:
    db "X"

times 510-($-$$)db 0
dw 0xAA55