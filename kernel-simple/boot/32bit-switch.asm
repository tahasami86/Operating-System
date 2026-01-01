[bits 16]
switch_pm:
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0 ;last bit of cr0 to 1
    or  eax, 0x1
    mov cr0, eax
    jmp CODE_SEG:PROC_INT ;FAR JMP

[bits 32]
PROC_INT:
    mov ax,DATA_SEG
    mov ss,ax
    mov ds,ax
    mov es,ax
    mov gs,ax
    mov fs,ax

    mov ebp,0x90000
    mov esp,ebp

    call BEGIN_PM