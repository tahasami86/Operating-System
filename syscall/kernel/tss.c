#include "tss.h"

struct tss_entry tss;

void tss_init(u32 idx, u32 kernel_ss, u32 kernel_esp) 
{
    u32 base = (u32)&tss;
    u32 limit = sizeof(tss);

    gdt_set_gate(6, base, limit, 0xE9, 0x00); // TSS segment

    //zero out the TSS
    memset(&tss, 0, sizeof(tss));

    tss.ss0 = kernel_ss; // Set the kernel stack segment
    tss.esp0 = kernel_esp; // Set the kernel stack pointer

    //set I/O map base to end of TSS
    tss.iomap_base = sizeof(tss);

    // Load TSS (selector = idx * 8)
    tss_flush(idx * 8);
}


void tss_set_kernel_stack(u32 stack) {
    tss.esp0 = stack;
}