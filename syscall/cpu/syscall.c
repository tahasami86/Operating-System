
#include "../drivers/screens.h"
#include "../cpu/isr.h"
#include "../libc/string.h"
#include "syscall.h"
#include "../kernel/kernel.h"

// System call table
typedef void (*syscall_t)(register_t*);


void sys_print(register_t *reg){
    char *str = (char *)reg->ebx;
        kprint(str);
}


void sys_read(register_t *reg){

}

void sys_exit(register_t *reg){
    kprint("\nProcess exited with code: ");
    char code_str[16];
    int_to_ascii(reg->ebx,code_str);
    kprint(code_str);
    kprint("\n");


}

void sys_yield(register_t *reg){

}

syscall_t syscall_table[256] = {
        [0] = sys_print,
        [1] = sys_read,
        [2] = sys_exit,
        [3] = sys_yield
};

void syscall_handler(register_t *reg){
    int syscall_num = reg->eax;

    if(syscall_num >=256 || syscall_table[reg->eax] == NULL ){
        kprint("Invalid syscall number \n");
        return;
    }
    syscall_t handler = syscall_table[syscall_num];

    if(handler){
        // Call the handler
        // Arguments are in: EBX, ECX, EDX, ESI, EDI
        handler(reg);
    }
    else{
        kprint("syscall not implemented \n");
    }
}

// User mode wrapper functions (to be used in user mode code)
void user_print(char *str){
    asm volatile("mov $0, %%eax \n"     // syscall number 0 (sys_print)
                 "mov %0, %%ebx \n"     // argument: string pointer
                 "int $0x80 \n"         // trigger syscall interrupt
                 : : "r"(str)
                 : "eax", "ebx"
    
    );
}

void user_exit(int code){
    asm volatile("mov $2, %%eax\n"      // syscall number 2 (sys_exit)
                 "mov %0, %%ebx\n"      // argument: exit code
                 "int $0x80 \n"         // trigger syscall interrupt
                 : : "r"(code)
                 : "eax","ebx"
    
    );
}