#include "idt.h"
#include "../kernel/util.h"

igdt_gate_t idt[IGDT_ENTRIES];
igdt_register_t idt_reg;

void set_idt_gate(int n, u32 handlers,u8 flags){
    idt[n].low_offset = low_16(handlers);
    idt[n].sel = KERNEL_CS;
    idt[n].always0 = 0 ;
    idt[n].flags = flags;
    idt[n].high_offset = high_16(handlers);
}

void set_idt(){
    idt_reg.base = (u32) &idt;
    //idt_reg.base = (u32) 0x2080;

    idt_reg.limit = IGDT_ENTRIES * (sizeof(igdt_gate_t)) - 1;
    /* Don't make the mistake of loading &idt -- always load &idt_reg */
    __asm__ __volatile__("lidtl (%0)" : : "r" (&idt_reg));

}
