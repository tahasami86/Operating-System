print_hex:
    pusha

    mov cx,0

;get the last char of 'dx', then convert to ASCII
;Numeric ASCII values: '0' (ASCII 0x30) to '9' (0x39) so add 0x30 to N bytes
;For alphabetic characters A-F: 'A' (ASCII 0x41) to 'F' (0x46) so well ad 0x30 + N + 7
;Then, move the ASCII byte to the correct position on the resulting string using rotate

hex_loop:
    cmp cx,4
    je done

    mov ax,dx
    and ax,0x000F ;  0x1234 -> 0x0004 by masking first three to zeros
    add al,0x30   ; Convert to ASCII
    cmp al,0x39   ; check to see if al is greater than '9' if so we need to convert to A-F for ASCII
    jle step2
    add al,0x07   ; Convert to A-F


; 2. get the correct position of the string to place our ASCII char
; bx <- base address + string length - index of char
step2:

    mov bx, HEX_BUF + 5 ;base address of string + offset to last char
    sub bx,cx         ; move to correct position
    mov [bx], al      ; place ASCII char in string
    ror dx,4         ; shift right 4 bits to get next hex digit 0x1234 -> 0x4123 -> 0x3412 -> 0x2341 -> 0x1234

    add cx,1
    jmp hex_loop


done:
    mov bx,HEX_BUF
    call print

    popa
    ret

HEX_BUF:
    db "0x0000",0