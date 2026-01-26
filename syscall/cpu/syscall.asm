[extern syscall_handler]

global isr128

isr128:
    cli 
    push byte 0 ; Dummy error code
    push byte 128 ; Interrupt number(0x80)
    jmp syscall_common_stub

syscall_common_stub:
    pusha ;Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
    push ax,ds ; Lower 16-bits of eax = ds.
    push eax
    mov ax, 0x10  ; kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Push pointer to registers
    push esp ; registers_t *r
    ;Call Handler
    cld 
    call syscall_handler

    ; Restore registers
    pop ebx
    pop ebx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx
    popa

    add esp, 8 ; Cleans up the pushed error code and pushed ISR number
    iret    ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

; Function to switch to user mode
; global switch_to_user_mode

switch_to_user_mode:

    ; Set up segments for user mode
    mov ax,0x23  ;User data segment with RPL=3 (0x20 | 0x3)
    mov ds,ax
    mov es,ax
    mov gs,ax
    mov fs,ax

    ; Push user mode stack segment and pointer
    push 0x23 ;User data segment (SS)
    push esp  ;User stack pointer (ESP)

    ; Push EFLAGS with interrupts enabled
    pushf
    pop eax
    or eax,0x200 ; Set IF flag (enable interrupts)
    push eax

    ; Push user mode code segment and entry point
    push 0x1b  ; User code segment with RPL=3 (0x18 | 0x3)
    push user_mode_entry

    iret

[bits 32]
user_mode_entry:

    ; Now running in user mode (Ring 3)
    ; This will be  user mode shell entry point
    [extern user_shell]
    call user_shell
    
    ; If user shell returns, halt
    jmp $
