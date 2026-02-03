[GLOBAL gdt_flush]
[GLOBAL tss_flush]

gdt_flush:
    mov eax, [esp +4] ;GEt pointer to GDT Ptr
    lgdt [eax]       ;Load the GDT from that pointer

    ;Reload segment registers
    mov ax, 0x10  ;Data Segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:.flush  ; Far jum to reload CS (0x08 Kernel code segment)

.flush:
    ret

tss_flush:
    mov ax , [esp +4] ;Get the TSS segment selector
    ltr ax ;Load Task register with 
    ret

