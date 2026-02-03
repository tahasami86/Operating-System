
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

    while(1) {
        user_print("> ");

    }
}


void kernel_main() {
    isr_install();
    irq_install();

    syscall_init();

    // kprint("Type something, it will go through the kernel\n"
    //     "Type END to halt the CPU or PAGE to request a kmalloc()\n> ");

    kprint("Kernel loaded successfully!\n");
    kprint("Switching to user mode...\n\n");
    
    // Switch to user mode - this will call user_shell()
  //  switch_to_user_mode();

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





