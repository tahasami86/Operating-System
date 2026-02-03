; db Define bytes
; dw Define Word
; dd Define double words


gdt_start:
    dd 0x0 ; Null 
    dd 0x0 ; Null 

gdt_code:
    dw 0xFFFF       ; limit 0-15
    dw 0x0          ; base 0-15
    db 0x0          ; base 16-23 
    db 10011010b    ; Acces byte = 0x9A  
    db 11001111b    ; flags=1100 limit=1111
    db 0x0          ; Base=24-31

gdt_data:
    dw 0xFFFF       ;limit= 0-15
    dw 0x0          ; base= 0-15
    db 0x0          ; base= 16-23    
    db 10010010b    ; Acces Byte=0x92
    db 11001111b    ; flags=1100 limit=1111
    db 0x0            ;Base=24-31

gdt_user_code:  ; User code segment (0x18)
    dw 0xFFFF
    dw 0x0
    db 0x0
    db 11111010b    ;Access: Present, Ring 3, Code, Executable, Readable
    db 11001111b    ; Flags + Limit 16-19
    db 0x0          ; Base 24-31

gdt_user_data:  ; User data segment (0x20)
    dw 0xFFFF       ; Limit 0-15
    dw 0x0          ; Base 0-15
    db 0x0          ; Base 16-23
    db 11110010b    ; Access: Present, Ring 3, Data, Writable
    db 11001111b    ; Flags + Limit 16-19
    db 0x0          ; Base 24-31


gdt_end:


gdt_descriptor:
    dw gdt_end - gdt_start -1 ;size (16 bit), always one less of its true size
    dd gdt_start ; address (32 bit)

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
USER_CODE_SEG equ gdt_user_code - gdt_start  ; 0x18
USER_DATA_SEG equ gdt_user_data - gdt_start  ; 0x20