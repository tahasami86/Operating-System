
#include "../drivers/screens.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "kernel.h"
#include "../cpu/syscall.h"

int i=1;


void user_shell(){

    user_print("Welcome to User Mode Shell!\n");
    user_print("Running in Ring 3 (User Mode)\n");
    user_print("Type 'exit' to return to kernel\n\n");
    //volatile int x=0;
    while(1) {
        //user_print("> ");
       // x++;

    }
}


void kernel_main() {
    kprint("Initializing kernel...\n");

    // Step 1: Initialize GDT (must come first!)
    kprint("Setting up GDT...\n");
    gdt_init();
    
    // Step 2: Initialize ISRs and IRQs  
    kprint("Setting up interrupts...\n");
    isr_install();
    irq_install();
    
    // Step 3: Initialize TSS (CRITICAL before user mode!)
    kprint("Setting up TSS...\n");
    tss_init(5, 0x10, 0x90000);
    

    // Step 4: Initialize syscalls
    kprint("Setting up system calls...\n");
    syscall_init();

    kprint("Kernel loaded successfully!\n");
    kprint("Switching to user mode...\n\n");
    
    // Switch to user mode - this will call user_shell()
    switch_to_user_mode();

    // We should never reach here
    kprint("ERROR: Returned from user mode!\n");
}

void user_input(char *input) {
    if (strcmp(input, "END") == 0) {
        kprint("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }
    else if(strcmp(input,"PAGE") == 0){
        uint32_t phys_addr;
        u32 page = kmalloc(400+13, (i%2), &phys_addr);
        char page_str[16] = "";
        hex_to_ascii(page, page_str);
        char phys_str[16] = "";
        hex_to_ascii(phys_addr, phys_str);
        kprint("Page: ");
        kprint(page_str);
        kprint(", physical address: ");
        kprint(phys_str);
        kprint("\n");
    }
    kprint("You said: ");
    kprint(input);
    kprint("\n> ");
    i++;
}





