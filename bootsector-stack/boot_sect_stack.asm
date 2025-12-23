mov ah,0x0e

mov bp,0x8000 ; Address far away from the org 0x7c00 to net get overwritten
mov sp, bp    ; Stack is empty  sp pints to bp

push "A"
push "B"
push "C"


mov al, [0x7FFE] ; 0x8000 -2 
int 0x10        ; PRINTS A an example just to illustrate at what memory location
                 ; the character 'A' is stored  


; Accessign 0x8000 wont work only 0x7FFE and above
mov al, [0x8000]
int 0x10

;Recover characters from the stack using pop
;Because POP always works with 16-bit registers/memory
;But BIOS interrupt 0x10 expects the character in AL (8 bits)!
;we need to extract just the character part (lower 8 bits):

pop bx
mov al,bl
int 0x10 ;PRINTS C 

pop bx
mov al,bl
int 0x10 ;PRINTS B

pop bx
mov al,bl
int 0x10 ;PRINTS A

; data that has been pop'd from the stack is garbage now
mov al, [0x8000]
int 0x10

push "G"

mov al, [0x7FFE] ; 0x8000 -2
int 0x10 ; PRINTS G

pop bx
mov al,bl
int 0x10 ;PRINTS G



jmp $ ; Infinite loop to halt the CPU

times 510-($-$$) db 0
dw 0xAA55