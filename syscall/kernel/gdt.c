#include "gdt.h"

struct gdt_entry gdt[6];
struct gdt_ptr gdt_p;


gdt_set_gate(int num, u32 base, u32 limit, u8 access, u8 flags)
{
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = limit & 0xFFFF;

    gdt[num].access = access;
    gdt[num].flags = flags;
}

void gdt_init()
{
    gdt_p.limit = (sizeof(struct gdt_entry) * 6 - 1);
    gdt_p.base = (u32)&gdt;
    gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment
    gdt_set_gate(5, 0, 0, 0, 0);                // TSS segment
    
    gdt_flush((u32)&gdt_p);
}