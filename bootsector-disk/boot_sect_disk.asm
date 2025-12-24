disk_load:
    pusha  ; Save all general-purpose registers
    push dx ; Save DX register

    mov ah, 0x02 ; BIOS function to read sectors
    mov al,dh ; Number of sectors to read from DH
    mov cl,0x02 ; Start reading from sector 2 (first sector is 1)
    mov ch,0x00 ; Cylinder 0
    mov dh,0x00 ; Head 0

    int 0x13 ; Call BIOS disk service interrupt
    jc disk_error ; Jump if carry flag is set (error occurred)


    pop dx ; Restore DX register

    cmp al,dh ; BIOS also sets 'al' to the # of sectors read. Compare it
    jne sector_error ; If not equal, some sectors were not read

    popa  ; Restore all general-purpose registers
    ret


disk_error:
    mov bx,DISK_ERROR
    call print 
    call print_newline
    mov dh,ah ; Move error code to DH for printing
    call print_hex
    jmp disk_loop


sector_error:
    mov bx,SECTOR_ERROR
    call print


disk_loop:
    jmp $ ; Infinite loop to halt execution after error


DISK_ERROR:
    db "failed to read disk!",0

SECTOR_ERROR:
    db "Failed to read all sectors!",0