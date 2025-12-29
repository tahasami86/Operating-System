[bits 32] ;using 32 bit protected mode

VIDEO_MEMORY equ 0xb8000 
WHITE_ON_BLACK equ 0x0F 


print_string_pm:
    pusha
    mov edx,VIDEO_MEMORY

print_string_loop:
    mov al , [ebx] ; [ebx] is the address of our character
    mov ah, WHITE_ON_BLACK

    cmp al, 0 
    jmp print_string_done

    mov [edx],ax ; store character + attribute in video memory

    add ebx , 1  ; next cha
    add edx , 2  ; next video memory position

    jmp print_string_loop


print_string_done:
    popa
    ret